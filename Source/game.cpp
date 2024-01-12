#include "game.hpp"
#include "raymath.h"

float lineLength(Vector2 A, Vector2 B) noexcept
{
	return sqrtf(powf(B.x - A.x, 2) + powf(B.y - A.y, 2));
}

void Game::End() noexcept
{
	PlayerProjectiles.clear();
	EnemyProjectiles.clear();
	Walls.clear();
	Aliens.clear();
	score.highScore = score.CheckNewHighScore();
	gameState = State::ENDSCREEN;
}

void Game::Input() noexcept
{
	player.Input();
}

void Game::Update()
{
	switch (gameState)
	{
	case State::MENU:
		if (IsKeyPressed(KEY_SPACE))
		{
			gameState = State::RUNNING;
			SpawnWalls();
			player.lives = 3;
			score.scorepoints = 0;
		}
		break;

	case State::RUNNING:

		if (player.lives < 1)
		{
			return End();
		}

		if (IsKeyReleased(KEY_Q))
		{
			return End();
		}

		if (Aliens.size() < 1)
		{
			SpawnAliens();
		}

		player.Update();
		for (auto& alien : Aliens)
		{
			alien.Update();

			if (alien.position.y > GetScreenHeight() - player.player_base_height)
			{
				return End();
			}
		}

		for (auto& projectile : PlayerProjectiles)
		{
			projectile.Update();
		}

		for (auto& projectile : EnemyProjectiles)
		{
			projectile.Update();
		}

		
		cornerPos = { 0, static_cast<float>(player.player_base_height) };
		offset = lineLength(player.position, cornerPos) * -1;
		background.Update(offset / 15);

		PlayerBulletVsWall();
		EnemyBulletVsWall();
		BulletVsAlien();
		BulletVsPlayer();

		if (IsKeyPressed(KEY_SPACE))
		{
			const float window_height = static_cast<float>(GetScreenHeight());
			Vector2 tmpPos = { player.position.x - player.RADIUS / 2.0f, window_height - 130.0f }; //TODO: magical value
			constexpr auto SPEED = 15;
			PlayerProjectiles.emplace_back(tmpPos, SPEED);
		}

		if (shootTimer > 59)
		{
			const int randomAlienIndex = rand() % Aliens.size();
			[[gsl::suppress(bounds.4)]]
			Vector2 tmpPos = { Aliens[randomAlienIndex].position.x, Aliens[randomAlienIndex].position.y };
			constexpr auto SPEED = -15;
			EnemyProjectiles.emplace_back(tmpPos, SPEED);
			shootTimer = 0;
		}

		shootTimer += 1;

		DeleteDeadEntities();

	break;
	case State::ENDSCREEN:
		if (IsKeyPressed(KEY_ENTER) && !score.highScore)
		{
			gameState = State::MENU;
		}
		score.Update();

		break;
	}
}

void Game::Render() const noexcept
{
	switch (gameState)
	{
	case State::MENU:
		DrawText("SPACE INVADERS", 200, 100, 40, YELLOW);
		DrawText("PRESS SPACE TO BEGIN", 200, 350, 40, YELLOW);

		break;
	case State::RUNNING:
		background.Render();
	
		DrawText(TextFormat("Score: %i", score.scorepoints), 50, 20, 40, YELLOW);
		DrawText(TextFormat("Lives: %i", player.lives), 50, 70, 40, YELLOW);

		[[gsl::suppress(bounds.4)]]
		player.Render(resources.shipTextures[player.activeTexture].get());

		for (const auto& projectile : PlayerProjectiles)
		{
			projectile.Render(resources.laserTexture.get());
		}

		for (const auto& projectile : EnemyProjectiles)
		{
			projectile.Render(resources.laserTexture.get());
		}

		for (const auto& wall : Walls)
		{
			wall.Render(resources.barrierTexture.get());
		}

		for (const auto& alien : Aliens)
		{
			alien.Render(resources.alienTexture.get());
		}

		break;
	case State::ENDSCREEN:
		score.Render();
		break;
	}
}

void Game::SpawnAliens()
{
	for (int row = 0; row < entityData.formationHeight; row++) 
	{
		for (int col = 0; col < entityData.formationWidth; col++) 
		{
			Vector2 tmpPos = { static_cast<float>(entityData.formationX + 50 + (col * entityData.alienSpacing)), static_cast<float>(entityData.formationY + (row * entityData.alienSpacing)) };
			Aliens.emplace_back(tmpPos);
		}
	}
}

void Game::SpawnWalls()
{
	const float wall_distance = GetScreenWidthF() / (wallCount + 1);
	for (int i = 0; i < wallCount; i++)
	{
		Vector2 tmpPos = { wall_distance * (i + 1.0f), GetScreenHeightF() - 250.0f };			
		Walls.emplace_back(tmpPos);
	}
}

bool Game::CheckCollision(Vector2 circlePos, float circleRadius, Vector2 lineStart, Vector2 lineEnd)
{
	if (CheckCollisionPointCircle(lineStart, circlePos, circleRadius) || CheckCollisionPointCircle(lineEnd, circlePos, circleRadius)) 
	{ 
		return true;
	}

	const auto A = lineStart;
	const auto B = lineEnd;
	const auto C = circlePos;
	const float length = Vector2Distance(A, B);
	const float dotP = Vector2DotProduct(Vector2Subtract(C, A), Vector2Subtract(B, A)) / std::powf(length, 2);
	const float closestX = A.x + dotP * (B.x - A.x), closestY = A.y + dotP * (B.y - A.y);
	
	[[gsl::suppress(con.5)]]
	const float buffer = 0.1f;
	const float closeToStart = Vector2Distance(A, { closestX, closestY });
	const float closeToEnd = Vector2Distance(B, { closestX, closestY });
	const float closestLength = closeToStart + closeToEnd;

	if (std::abs(closestLength - length) < buffer)
	{
		return Vector2Distance(C, { closestX, closestY }) < circleRadius;
	}

	return false;
}

void Game::BulletVsPlayer()
{
	for (auto& projectile : EnemyProjectiles)
	{
		if (CheckCollision({ player.position.x, GetScreenHeightF() - player.player_base_height },
			static_cast<float>(player.RADIUS),
			projectile.lineStart,
			projectile.lineEnd))
		{
			projectile.active = false;
			player.lives -= 1;
		}
	}
}

void Game::BulletVsAlien()
{
	for (auto& projectile : PlayerProjectiles)
	{
		for (auto& alien : Aliens)
		{
			if (CheckCollision(alien.position, Alien::RADIUS, projectile.lineStart, projectile.lineEnd))
			{
				projectile.active = false;
				alien.active = false;
				score.scorepoints += 100;
			}
		}
	}
}

void Game::PlayerBulletVsWall()
{
	for (auto& projectile : PlayerProjectiles)
	{
		for (auto& wall : Walls)
		{
			if (CheckCollision(wall.position, Wall::RADIUS, projectile.lineStart, projectile.lineEnd))
			{
				projectile.active = false;
				wall.health -= 1;
				if (wall.health < 1)
				{
					wall.active = false;
				}
			}
		}
	}
}

void Game::EnemyBulletVsWall()
{
	for (auto& projectile : EnemyProjectiles)
	{
		for (auto& wall : Walls)
		{
			if (CheckCollision(wall.position, Wall::RADIUS, projectile.lineStart, projectile.lineEnd))
			{
				projectile.active = false;
				wall.health -= 1;
				if (wall.health < 1)
				{
					wall.active = false;
				}
			}
		}
	}
}

void Game::DeleteDeadEntities()
{
	static constexpr auto isDead = [](const auto& x) constexpr noexcept { return x.active == false; };
 	std::erase_if(PlayerProjectiles, isDead);
	std::erase_if(EnemyProjectiles, isDead);
	std::erase_if(Aliens, isDead);
	std::erase_if(Walls, isDead);
}
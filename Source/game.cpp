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

		IsGameEnding();

		if (Aliens.size() < 1)
		{
			SpawnAliens();
		}

		UpdateAll();
		
		cornerPos = { 0, static_cast<float>(player.player_base_height) };
		offset = lineLength(player.position, cornerPos) * -1;
		background.Update(offset / 15);

		PlayerBulletVsWall();
		EnemyBulletVsWall();
		BulletVsAlien();
		BulletVsPlayer();

		PlayerShouldShoot();
		AlienShouldShoot();

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

		RenderAll();

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
	Walls.reserve(wallCount);
	for (int i = 0; i < wallCount; i++)
	{
		Vector2 tmpPos = { wall_distance * (i + 1.0f), GetScreenHeightF() - 250.0f };			
		Walls.emplace_back(tmpPos);
	}
}

void Game::IsGameEnding() noexcept
{
	if (player.lives < 1)
	{
		return End();
	}

	if (IsKeyReleased(KEY_Q))
	{
		return End();
	}

	for (auto& alien : Aliens)
	{
		if (alien.position.y > GetScreenHeight() - player.player_base_height)
		{
			return End();
		}
	}
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
			return;
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
				return;
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
				return;
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
				return;
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

void Game::CollidesWithWalls(const Rectangle& rect)
{

}

void Game::CollidesWithPlayer(const Rectangle& rect)
{

}

void Game::CollidesWithAliens(const Rectangle& rect)
{

}

void Game::AlienShouldShoot() noexcept
{
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
}

void Game::PlayerShouldShoot() noexcept
{
	if (IsKeyPressed(KEY_SPACE))
	{
		const float window_height = static_cast<float>(GetScreenHeight());
		Vector2 tmpPos = { player.position.x - player.RADIUS / 2.0f, window_height - 130.0f }; //TODO: magical value
		constexpr auto SPEED = 15;
		PlayerProjectiles.emplace_back(tmpPos, SPEED);
	}
}

void Game::RenderAll() const noexcept
{
	background.Render();

	DrawText(TextFormat("Score: %i", score.scorepoints), 50, 20, 40, YELLOW);
	DrawText(TextFormat("Lives: %i", player.lives), 50, 70, 40, YELLOW);

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
}

void Game::UpdateAll() noexcept
{
	player.Update();
	for (auto& alien : Aliens)
	{
		alien.Update();
	}

	for (auto& projectile : PlayerProjectiles)
	{
		projectile.Update();
	}

	for (auto& projectile : EnemyProjectiles)
	{
		projectile.Update();
	}
}

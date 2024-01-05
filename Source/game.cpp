#include "game.hpp"
#include "Wall.hpp"
#include "Alien.hpp"
#include "Projectile.hpp"
#include "algorithm"
#include "raymath.h"

float lineLength(Vector2 A, Vector2 B) noexcept
{
	const float length = sqrtf(static_cast<float>(pow(B.x - A.x, 2) + pow(B.y - A.y, 2)));

	return length;
}

bool pointInCircle(Vector2 circlePos, float RADIUS, Vector2 point) noexcept
{
	const float distanceToCentre = lineLength(circlePos, point);

	if (distanceToCentre < RADIUS)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Game::End() noexcept
{
	PlayerProjectiles.clear();
	EnemyProjectiles.clear();
	Walls.clear();
	Aliens.clear();
	newHighScore = CheckNewHighScore();
	gameState = State::ENDSCREEN;
}

void Game::Continue() noexcept
{
	gameState = State::MENU;
}

void Game::Input() noexcept
{
	player.Input();
}

void Game::Update() noexcept
{
	switch (gameState)
	{
	case State::MENU:
		if (IsKeyPressed(KEY_SPACE))
		{
			gameState = State::RUNNING;
			SpawnWalls();
			score = 0;
			player.lives = 3;
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

		for (auto& wall : Walls)
		{
			wall.Update();
		}

		playerPos = { static_cast<float>(player.PosX), static_cast<float>(player.player_base_height) };
		cornerPos = { 0, static_cast<float>(player.player_base_height) };
		offset = lineLength(playerPos, cornerPos) * -1;
		background.Update(offset / 15);

		PlayerBulletVsWall();
		EnemyBulletVsWall();
		BulletVsAlien();
		BulletVsPlayer();

		if (IsKeyPressed(KEY_SPACE))
		{
			const float window_height = static_cast<float>(GetScreenHeight());
			Vector2 tmpPos = { static_cast<float>(player.PosX), window_height - 130 }; //TODO: magical value
			PlayerProjectiles.emplace_back(tmpPos, BulletType::PLAYER_PROJECTILE);
		}

		if (shootTimer > 59)
		{
			const int randomAlienIndex = rand() % Aliens.size();

			Vector2 tmpPos = { Aliens[randomAlienIndex].position.x, Aliens[randomAlienIndex].position.y };
			EnemyProjectiles.emplace_back(tmpPos, BulletType::ENEMY_PROJECTILE);
			shootTimer = 0;
		}

		shootTimer += 1;

		DeleteDeadEntities();

	break;
	case State::ENDSCREEN:
		if (IsKeyReleased(KEY_ENTER) && !newHighScore)
		{
			Continue();
		}

		if (newHighScore)
		{
			const int key = GetCharPressed();

			if (key > 0)
			{
				name.push_back(static_cast<char>(key));
				letterCount++;
			}

			if (IsKeyPressed(KEY_BACKSPACE) && name.size() > 0)
			{
				name.pop_back();
			}

			if (letterCount > 0 && letterCount < 9 && IsKeyReleased(KEY_ENTER))
			{
				InsertNewHighScore(name);

				newHighScore = false;
			}
		}

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
	
		DrawText(TextFormat("Score: %i", score), 50, 20, 40, YELLOW);
		DrawText(TextFormat("Lives: %i", player.lives), 50, 70, 40, YELLOW);

		player.Render(resources.shipTextures[player.activeTexture].get());

		for (auto& projectile : PlayerProjectiles)
		{
			projectile.Render(resources.laserTexture.get());
		}

		for (auto& projectile : EnemyProjectiles)
		{
			projectile.Render(resources.laserTexture.get());
		}

		for (auto& wall : Walls)
		{
			wall.Render(resources.barrierTexture.get());
		}

		for (auto& alien : Aliens)
		{
			alien.Render(resources.alienTexture.get());
		}

		break;
	case State::ENDSCREEN:

		if (newHighScore)
		{
			DrawText("NEW HIGHSCORE!", 600, 300, 60, YELLOW);

			DrawText("Write your name", 600, 400, 20, YELLOW);

			DrawRectangleRec(textBox, LIGHTGRAY);
			
			DrawRectangleLines(static_cast<int>(textBox.x), static_cast<int>(textBox.y), static_cast<int>(textBox.width), static_cast<int>(textBox.height), RED);

			DrawText(name.data(), static_cast<int>(textBox.x) + 5, static_cast<int>(textBox.y) + 8, 40, MAROON);

			DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, name.capacity()), 600, 600, 20, YELLOW);

			if (letterCount < name.capacity())
			{
				DrawText("_", static_cast<int>(textBox.x) + 8 + MeasureText(name.data(), 40), static_cast<int>(textBox.y) + 12, 40, MAROON);
			}
			else
			{
				DrawText("Press BACKSPACE to delete chars...", 600, 650, 20, YELLOW);
			}

			if (letterCount > 0 && letterCount < name.capacity())
			{
				DrawText("PRESS ENTER TO CONTINUE", 600, 800, 40, YELLOW);
			}

		}
		else 
		{
			DrawText("PRESS ENTER TO CONTINUE", 600, 200, 40, YELLOW);

			DrawText("LEADERBOARD", 50, 100, 40, YELLOW);

			for (int i = 0; i < Leaderboard.size(); i++)
			{
				const std::string_view tempNameDisplay = Leaderboard[i].name.data();
				DrawText(tempNameDisplay.data(), 50, 140 + (i * 40), 40, YELLOW);
				DrawText(TextFormat("%i", Leaderboard[i].score), 350, 140 + (i * 40), 40, YELLOW);
			}
		}
		break;
	}
}

void Game::SpawnAliens()
{
	EntityPositioningData data;
	for (int row = 0; row < data.formationHeight; row++) 
	{
		for (int col = 0; col < data.formationWidth; col++) 
		{
			Vector2 tmpPos = { static_cast<float>(data.formationX + 50 + (col * data.alienSpacing)), static_cast<float>(data.formationY + (row * data.alienSpacing)) };
			Aliens.emplace_back(tmpPos);
		}
	}
}

void Game::SpawnWalls()
{
	const float wall_distance = static_cast<float>(GetScreenWidth() / wallCount);
	for (int i = 0; i < wallCount; i++)
	{
		Vector2 tmpPos = { wall_distance * (i + 1), static_cast<float>(GetScreenHeight()) - 250.0f };
		Walls.emplace_back(tmpPos);
	}
}

bool Game::CheckNewHighScore() noexcept
{
	return (score > Leaderboard[4].score);
}

bool Game::InsertNewHighScore(std::string_view Name)
{
	Data.name = Name;
	Data.score = score;

	static constexpr auto isHigher = [&](auto& a, auto& b) { return a.score > b.score; };

	Leaderboard.push_back(Data);
	std::ranges::sort(Leaderboard, isHigher);
	Leaderboard.pop_back();

	return true;
}

bool Game::CheckCollision(Vector2 circlePos, float circleRadius, Vector2 lineStart, Vector2 lineEnd) noexcept
{
	if (CheckCollisionPointCircle(lineStart, circlePos, circleRadius) || CheckCollisionPointCircle(lineEnd, circlePos, circleRadius))
		return true;

	const auto A = lineStart, B = lineEnd, C = circlePos;
	const float length = Vector2Distance(A, B);
	const float dotP = Vector2DotProduct(Vector2Subtract(C, A), Vector2Subtract(B, A)) / static_cast<float>(std::pow(length, 2));
	const float closestX = A.x + dotP * (B.x - A.x), closestY = A.y + dotP * (B.y - A.y);

	const float buffer = 0.1f;
	const float closeToStart = Vector2Distance(A, { closestX, closestY }), closeToEnd = Vector2Distance(B, { closestX, closestY });
	const float closestLength = closeToStart + closeToEnd;

	if (std::abs(closestLength - length) < buffer)
		return Vector2Distance(C, { closestX, closestY }) < circleRadius;

	return false;
}

void Game::BulletVsPlayer() noexcept
{
	for (auto& projectile : EnemyProjectiles)
	{
		if (CheckCollision({ static_cast<float>(player.PosX), GetScreenHeight() - player.player_base_height },
			static_cast<float>(player.RADIUS),
			projectile.lineStart,
			projectile.lineEnd))
		{
			projectile.active = false;
			player.lives -= 1;
		}
	}
}

void Game::BulletVsAlien() noexcept
{
	for (auto& projectile : PlayerProjectiles)
	{
		for (auto& alien : Aliens)
		{
			if (CheckCollision(alien.position, alien.RADIUS, projectile.lineStart, projectile.lineEnd))
			{
				projectile.active = false;
				alien.active = false;
				score += 100;
			}
		}
	}
}

void Game::PlayerBulletVsWall() noexcept
{
	for (auto& projectile : PlayerProjectiles)
	{
		for (auto& wall : Walls)
		{
			if (CheckCollision(wall.position, wall.RADIUS, projectile.lineStart, projectile.lineEnd))
			{
				projectile.active = false;
				wall.health -= 1;
			}
		}
	}
}

void Game::EnemyBulletVsWall() noexcept
{
	for (auto& projectile : EnemyProjectiles)
	{
		for (auto& wall : Walls)
		{
			if (CheckCollision(wall.position, wall.RADIUS, projectile.lineStart, projectile.lineEnd))
			{
				projectile.active = false;
				wall.health -= 1;
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

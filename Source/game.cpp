#include "game.hpp"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>

float lineLength(Vector2 A, Vector2 B) //TODO: Make into a helper function
{
	float length = sqrtf(static_cast<float>(pow(B.x - A.x, 2) + pow(B.y - A.y, 2)));

	return length;
}

bool pointInCircle(Vector2 circlePos, float radius, Vector2 point) //TODO: Make into a helper function
{
	float distanceToCentre = lineLength(circlePos, point);

	if (distanceToCentre < radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Game::Game()
{
	SpawnWalls();
	SpawnAliens();

	score = 0;
}

void Game::End()
{
	Projectiles.clear();
	Walls.clear();
	Aliens.clear();
	newHighScore = CheckNewHighScore();
	gameState = State::ENDSCREEN;
}

void Game::Continue()
{
	gameState = State::MENU;
}

void Game::Input()
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
		for (auto& aliens : Aliens) //TODO: Make into a for each
		{
			aliens.Update();

			if (aliens.position.y > GetScreenHeight() - player.player_base_height)
			{
				return End();
			}
		}

		for (auto& projectile : Projectiles) //TODO: Make into a for each
		{
			projectile.Update();
		}

		for (auto& wall : Walls) //TODO: Make into a for each
		{
			wall.Update();
		}

		playerPos = { static_cast<float>(player.PosX), static_cast<float>(player.player_base_height) }; //Make a get function?
		cornerPos = { 0, (float)player.player_base_height };
		offset = lineLength(playerPos, cornerPos) * -1;
		background.Update(offset / 15);

		BulletVsWall();
		BulletVsAlien();
		BulletVsPlayer();

		if (IsKeyPressed(KEY_SPACE))
		{
			float window_height = static_cast<float>(GetScreenHeight());
			Vector2 tmpPos = { static_cast<float>(player.PosX), window_height - 130 };
			Projectiles.emplace_back(tmpPos, EntityType::PLAYER_PROJECTILE);
		}

		if (shootTimer > 59)
		{
			int randomAlienIndex = rand() % Aliens.size();

			Vector2 tmpPos = { Aliens[randomAlienIndex].position.x, Aliens[randomAlienIndex].position.y };
			Projectiles.emplace_back(tmpPos, EntityType::ENEMY_PROJECTILE);
			shootTimer = 0;
		}

		shootTimer += 1;

		DeleteDeadEntities();

	break;
	case State::ENDSCREEN:
		if (IsKeyReleased(KEY_ENTER) && !newHighScore)
		{
			Continue();
			//TODO: Reset all values
		}

		if (newHighScore)
		{
			if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
			else mouseOnText = false;

			if (mouseOnText)
			{
				SetMouseCursor(MOUSE_CURSOR_IBEAM);

				int key = GetCharPressed(); //TODO: Lets use the raylib keybindings

				while (key > 0)
				{
					if ((key >= 32) && (key <= 125) && (letterCount < 9))
					{
						name[letterCount] = (char)key;
						name[letterCount + 1] = '\0';
						letterCount++;
					}

					key = GetCharPressed();
				}

				if (IsKeyPressed(KEY_BACKSPACE))
				{
					letterCount--;
					if (letterCount < 0) letterCount = 0;
					name[letterCount] = '\0';
				}
			}
			else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

			if (mouseOnText)
			{
				framesCounter++;
			}
			else
			{
				framesCounter = 0;
			}

			if (letterCount > 0 && letterCount < 9 && IsKeyReleased(KEY_ENTER))
			{
				std::string nameEntry(name);

				InsertNewHighScore(nameEntry);

				newHighScore = false;
			}
		}

		break;
	default:
		break;
	}
}


void Game::Render()
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
		for (auto& projectile : Projectiles)
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

			DrawText("PLACE MOUSE OVER INPUT BOX!", 600, 400, 20, YELLOW);

			DrawRectangleRec(textBox, LIGHTGRAY);
			if (mouseOnText)
			{
				DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
			}
			else
			{
				DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);
			}
			DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

			DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, 8), 600, 600, 20, YELLOW);

			if (mouseOnText)
			{
				if (letterCount < 9)
				{
					if (((framesCounter / 20) % 2) == 0)
					{
						DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
					}
				}
				else
				{
					DrawText("Press BACKSPACE to delete chars...", 600, 650, 20, YELLOW);
				}
				
			}

			if (letterCount > 0 && letterCount < 9)
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
				char* tempNameDisplay = Leaderboard[i].name.data(); //TODO: Use string instead of char
				DrawText(tempNameDisplay, 50, 140 + (i * 40), 40, YELLOW);
				DrawText(TextFormat("%i", Leaderboard[i].score), 350, 140 + (i * 40), 40, YELLOW);
			}
		}
		break;
	}
}

void Game::SpawnAliens()
{
	for (int row = 0; row < formationHeight; row++) 
	{
		for (int col = 0; col < formationWidth; col++) 
		{
			Vector2 tmpPos = { static_cast<float>(formationX + 50 + (col * alienSpacing)), static_cast<float>(formationY + (row * alienSpacing)) };
			Aliens.emplace_back(tmpPos);
		}
	}
}

void Game::SpawnWalls()
{
	float wall_distance = static_cast<float>(GetScreenWidth() / (wallCount + 1.0f));
	for (int i = 0; i < wallCount; i++)
	{
		Vector2 tmpPos = { wall_distance * (i + 1), static_cast<float>(GetScreenHeight()) - 250.0f };
		Walls.emplace_back(tmpPos);
	}
}

bool Game::CheckNewHighScore()
{
	if (score > Leaderboard[4].score)
	{
		return true;
	}
	return false;
}

void Game::InsertNewHighScore(std::string Name)
{
	PlayerData newData;
	newData.name = Name;
	newData.score = score;

	for (int i = 0; i < Leaderboard.size(); i++)
	{
		if (newData.score > Leaderboard[i].score)
		{

			Leaderboard.insert(Leaderboard.begin() + i, newData);

			Leaderboard.pop_back();

			break;
		}
	}
}

bool Game::CheckCollision(Vector2 circlePos, float circleRadius, Vector2 lineStart, Vector2 lineEnd)
{
	// our objective is to calculate the distance between the closest point on the line to the centre of the circle, 
	// and determine if it is shorter than the radius.

	// check if either edge of line is within circle
	if (pointInCircle(circlePos, circleRadius, lineStart) || pointInCircle(circlePos, circleRadius, lineEnd))
	{
		return true;
	}

	// simplify variables
	Vector2 A = lineStart;
	Vector2 B = lineEnd;
	Vector2 C = circlePos;

	// calculate the length of the line
	float length = lineLength(A, B);
	
	// calculate the dot product
	float dotP = (((C.x - A.x) * (B.x - A.x)) + ((C.y - A.y) * (B.y - A.y))) / static_cast<float>(pow(length, 2));

	// use dot product to find closest point
	float closestX = A.x + (dotP * (B.x - A.x));
	float closestY = A.y + (dotP * (B.y - A.y));

	//find out if coordinates are on the line.
	// we do this by comparing the distance of the dot to the edges, with two vectors
	// if the distance of the vectors combined is the same as the length the point is on the line

	//since we are using floating points, we will allow the distance to be slightly innaccurate to create a smoother collision
	float buffer = 0.1f;

	float closeToStart = lineLength(A, { closestX, closestY }); //closestX + Y compared to line Start
	float closeToEnd = lineLength(B, { closestX, closestY });	//closestX + Y compared to line End

	float closestLength = closeToStart + closeToEnd;

	if (closestLength == length + buffer || closestLength == length - buffer)
	{
		//Point is on the line!

		//Compare length between closest point and circle centre with circle radius

		float closeToCentre = lineLength(A, { closestX, closestY }); //closestX + Y compared to circle centre

		if (closeToCentre < circleRadius)
		{
			//Line is colliding with circle!
			return true;
		}
		else
		{
			//Line is not colliding
			return false;
		}
	}
	else
	{
		// Point is not on the line, line is not colliding
		return false;
	}
}

void Game::BulletVsPlayer()
{
	for (auto& projectile : Projectiles) //TODO: Make into a for each
	{
		if (projectile.type == EntityType::ENEMY_PROJECTILE)
		{
			if (CheckCollision({ static_cast<float>(player.PosX), GetScreenHeight() - player.player_base_height },
				static_cast<float>(player.radius),
				projectile.lineStart,
				projectile.lineEnd))
			{
				projectile.active = false;
				player.lives -= 1;
			}
		}
	}
}

void Game::BulletVsAlien()
{
	for (auto& projectile : Projectiles) //TODO: Make into a for each
	{
		if (projectile.type == EntityType::PLAYER_PROJECTILE)
		{
			for (auto& alien : Aliens) //TODO: Make into a for each
			{
				if (CheckCollision(alien.position, alien.radius, projectile.lineStart, projectile.lineEnd))
				{
					projectile.active = false;
					alien.active = false;
					score += 100;
				}
			}
		}
	}
}

void Game::BulletVsWall()
{
	for (auto& projectile : Projectiles) //TODO: Make into a for each
	{
		for (auto& wall : Walls) //TODO: Make into a for each
		{
			if (CheckCollision(wall.position, wall.radius, projectile.lineStart, projectile.lineEnd))
			{
				projectile.active = false;
				wall.health -= 1;
			}
		}
	}
}

void Game::DeleteDeadEntities()
{
	//TODO: Maybe an algorithm for this
	for (int i = 0; i < Projectiles.size(); i++)
	{
		if (Projectiles[i].active == false)
		{
			Projectiles.erase(Projectiles.begin() + i);
			i--;
		}
	}
	for (int i = 0; i < Aliens.size(); i++)
	{
		if (Aliens[i].active == false)
		{
			Aliens.erase(Aliens.begin() + i);
			i--;
		}
	}
	for (int i = 0; i < Walls.size(); i++)
	{
		if (Walls[i].active == false)
		{
			Walls.erase(Walls.begin() + i);
			i--;
		}
	}
}

#pragma once
#include "raylib.h"
#include <vector>
#include "Background.hpp"
#include "Resources.hpp"
#include <string>
#include "Alien.hpp"
#include "Player.hpp"
#include "Projectile.hpp"
#include "Wall.hpp"

enum struct State
{
	MENU,
	RUNNING,
	ENDSCREEN
}; 

struct PlayerData //TODO: Make a score class that keeps track of score and name
{
	std::string name; //TODO: Initialize variables that are declared
	int score;
};

class Game
{
public:
	Game();
	State gameState = State::MENU;

	int score = 0;

	int wallCount = 5;

	float shootTimer = 0;

	Rectangle rec = { 0, 0 ,0 ,0 }; 

	int formationWidth = 8;
	int formationHeight = 5;
	int alienSpacing = 80;
	int formationX = 100;
	int formationY = 50;

	bool newHighScore = false;

	void End();

	void Continue();

	void Input();
	void Update();
	void Render();

	void SpawnAliens();
	void SpawnWalls();

	bool CheckCollision(Vector2 circlePos, float circleRadius, Vector2 lineTop, Vector2 lineBottom);

	void BulletVsPlayer();
	void BulletVsAlien();
	void BulletVsWall();
	void DeleteDeadEntities();

	bool CheckNewHighScore();

	void InsertNewHighScore(std::string name);

	Resources resources;

	Player player{ GetScreenWidth() / 2 };

	std::vector<Projectile> Projectiles;

	std::vector<Wall> Walls;

	std::vector<Alien> Aliens;

	std::vector<PlayerData> Leaderboard = { {"Player 1", 500}, {"Player 2", 400}, {"Player 3", 300}, {"Player 4", 200}, {"Player 5", 100} };

	Background background;

	Vector2 playerPos = {}; //TODO: Initialize variables that are declared
	Vector2 alienPos = {};
	Vector2 cornerPos = {};
	float offset = 0;

	char name[9 + 1] = "\0"; //TODO: Use string not char
	int letterCount = 0;

	Rectangle textBox = { 600, 500, 225, 50 };
	bool mouseOnText = false;

	int framesCounter = 0;
};
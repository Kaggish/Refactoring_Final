#pragma once
#include "raylib.h"
#include "Background.hpp"
#include "Resources.hpp"
#include "Player.hpp"
#include "Wall.hpp"
#include "Alien.hpp"
#include "Projectile.hpp"
#include <vector>
#include <string>

enum struct State
{
	MENU,
	RUNNING,
	ENDSCREEN
}; 

struct PlayerData
{
	std::string name = {};
	int score = 0;
};

struct EntityPositioningData
{
	const int formationWidth = 8;
	const int formationHeight = 5;
	const int alienSpacing = 80;
	const int formationX = 100;
	const int formationY = 50;
};

class Game
{
	State gameState = State::MENU;

	bool newHighScore = false;

	float shootTimer = 0;

	const int wallCount = 5;
	int score = 0;
	int letterCount = 0;;

	Vector2 playerPos = {};
	Vector2 alienPos = {};
	Vector2 cornerPos = {};
	float offset = 0;

	std::string name = {};
	Rectangle textBox = { 600, 500, 225, 50 };

	Resources resources;

	Player player{ GetScreenWidth() / 2 };
	PlayerData Data;

	std::vector<Projectile> PlayerProjectiles;
	std::vector<Projectile> EnemyProjectiles;
	std::vector<Wall> Walls;
	std::vector<Alien> Aliens;
	std::vector<PlayerData> Leaderboard = { {"Player 1", 500}, {"Player 2", 400}, {"Player 3", 300}, {"Player 4", 200}, {"Player 5", 100} };

	Background background;

	void Continue() noexcept;
	void End() noexcept;

	void SpawnAliens();
	void SpawnWalls();

	bool CheckCollision(Vector2 circlePos, float circleRadius, Vector2 lineTop, Vector2 lineBottom) noexcept;

	void BulletVsPlayer() noexcept;
	void BulletVsAlien() noexcept;
	void PlayerBulletVsWall() noexcept;
	void EnemyBulletVsWall() noexcept;
	void DeleteDeadEntities();

	bool CheckNewHighScore() noexcept;

	bool InsertNewHighScore(std::string_view name);

public:
	void Input() noexcept;
	void Update() noexcept;
	void Render() const noexcept;
};
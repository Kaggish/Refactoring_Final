#pragma once

#include <codeanalysis\warnings.h>

#pragma warning(push)

#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)

#include <raylib.h>
#include <raymath.h>

#pragma warning(pop)

#include "Background.hpp"
#include "Resources.hpp"
#include "Player.hpp"
#include "Wall.hpp"
#include "Alien.hpp"
#include "Projectile.hpp"
#include "Score.hpp"
#include <vector>

enum struct State
{
	MENU,
	RUNNING,
	ENDSCREEN
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

	float shootTimer = 0;

	const int wallCount = 5;

	Vector2 playerPos = {};
	Vector2 alienPos = {};
	Vector2 cornerPos = {};
	float offset = 0;

	Resources resources;

	Player player;
	EntityPositioningData entityData;

	std::vector<Projectile> PlayerProjectiles;
	std::vector<Projectile> AlienProjectiles;
	std::vector<Wall> Walls;
	std::vector<Alien> Aliens;

	Score score;

	Background background;

	void End() noexcept;

	void SpawnAliens();
	void SpawnWalls();

	void IsGameEnding() noexcept;

	void PlayerBulletUpdate() noexcept;
	void AlienBulletUpdate() noexcept;

	void DeleteDeadEntities();
	bool CollidesWithWalls(const Rectangle& rect) noexcept;
	bool CollidesWithPlayer(const Rectangle& rect) noexcept;
	bool CollidesWithAliens(const Rectangle& rect) noexcept;

	void AlienShoot() noexcept;
	void PlayerShoot() noexcept;

	void RenderAll() const noexcept;
	void UpdateAll() noexcept;

public:
	void Input() noexcept;
	void Update();
	void Render() const noexcept;
};
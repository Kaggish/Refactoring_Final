#pragma once
#include "raylib.h"
#include <vector>
#include "Resources.hpp"
#include <string>
#include "Background.hpp"
#include "Alien.hpp"

//TODO: Remove redundant comments
enum struct State //TODO: Renaming for clarity and better naming
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

struct Player //TODO: Make into its own class
{
public:

	float x_pos = 0;
	float speed = 7;
	float player_base_height = 70.0f;  
	float radius = 50;
	int lives = 3;
	int direction = 0; //We don´t need direction really we are moving only in the X-axis
	int activeTexture = 0;
	float timer = 0;

	EntityType type = EntityType::PLAYER;

	void Initialize(); //Make into a constructor
	void Render(Texture2D texture);
	void Update();
	
};


struct Projectile //TODO: Make into its own class
{
public: 
	// INITIALIZE PROJECTILE WHILE DEFINING IF ITS PLAYER OR ENEMY 
	Vector2 position = {0,0};
	int speed = 15; 
	bool active = true;  
	EntityType type = {};

	// LINE WILL UPDATE WITH POSITION FOR CALCULATIONS
	Vector2 lineStart = { 0, 0 };
	Vector2 lineEnd = { 0, 0 };

	void Update();

	void Render(Texture2D texture);
};

struct Wall //TODO: Make into its own class
{
public: 
	Vector2 position; //TODO: Initialize variables that are declared
	Rectangle rec; 
	bool active; 
	Color color; 
	int health = 50;
	float radius = 60;


	void Render(Texture2D texture); 
	void Update(); 
};


class Game //Make it into a class
{
public:
	// Gamestate
	State gameState = {};

	// Score
	int score; //TODO: Initialize variables that are declared

	// for later, make a file where you can adjust the number of walls (config file) 
	int wallCount = 5;

	//Aliens shooting
	float shootTimer = 0;

	//Aliens stuff? (idk cause liv wrote this)
	Rectangle rec = { 0, 0 ,0 ,0 }; 

	int formationWidth = 8;
	int formationHeight = 5;
	int alienSpacing = 80;
	int formationX = 100;
	int formationY = 50;

	bool newHighScore = false;
	

	void Start();
	void End();

	void Continue();
	void Launch(); //TODO: Better naming

	void Update();
	void Render();

	void SpawnAliens();

	bool CheckCollision(Vector2 circlePos, float circleRadius, Vector2 lineTop, Vector2 lineBottom);

	bool CheckNewHighScore();

	void InsertNewHighScore(std::string name);

	// Entity Storage and Resources
	Resources resources;

	Player player;

	std::vector<Projectile> Projectiles;

	std::vector<Wall> Walls;

	std::vector<Alien> Aliens;

	std::vector<PlayerData> Leaderboard = { {"Player 1", 500}, {"Player 2", 400}, {"Player 3", 300}, {"Player 4", 200}, {"Player 5", 100} };

	Background background;

	Vector2 playerPos; //TODO: Initialize variables that are declared
	Vector2 alienPos; 
	Vector2 cornerPos;
	float offset;


	//TEXTBOX ENTER
	char name[9 + 1] = "\0"; //TODO: Use string not char
	//One extra space required for null terminator char '\0'
	int letterCount = 0;

	Rectangle textBox = { 600, 500, 225, 50 };
	bool mouseOnText = false;

	int framesCounter = 0;

};
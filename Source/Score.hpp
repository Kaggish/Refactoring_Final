#pragma once
#include "raylib.h"
#include <string>
#include <vector>

class Score
{
	std::string name = {};

	Rectangle textBox = { 600, 500, 225, 50 };

	std::vector<std::pair<std::string, int>> Leaderboard = { {"Player 1", 500}, {"Player 2", 400}, {"Player 3", 300}, {"Player 4", 200}, {"Player 5", 100} };

	bool InsertNewHighScore();

public:
	int scorepoints = 0;
	bool highScore = false;

	bool CheckNewHighScore() const noexcept;
	void Update();
	void Render() const noexcept;
};
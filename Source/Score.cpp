#include "Score.hpp"
#include <algorithm>

void Score::Update()
{
	if (highScore)
	{
		const int key = GetCharPressed();

		if (key > 32 && key < 127)
		{
			name.push_back(static_cast<char>(key));
		}

		if (IsKeyPressed(KEY_BACKSPACE) && name.size() > 0)
		{
			name.pop_back();
		}

		if (name.size() > 0 && name.size() < letterCap && IsKeyPressed(KEY_ENTER))
		{
			InsertNewHighScore();
			name.clear();
			highScore = false;
		}
	}
}

void Score::Render() const noexcept
{
	if (highScore)
	{
		DrawText("NEW HIGHSCORE!", 600, 300, 60, YELLOW);

		DrawText("Write your name", 600, 400, 20, YELLOW);

		DrawRectangleRec(textBox, LIGHTGRAY);

		DrawRectangleLines(static_cast<int>(textBox.x), static_cast<int>(textBox.y), static_cast<int>(textBox.width), static_cast<int>(textBox.height), RED);

		DrawText(name.data(), static_cast<int>(textBox.x) + 5, static_cast<int>(textBox.y) + 8, 40, MAROON);

		DrawText(TextFormat("INPUT CHARS: %i/%i", name.size(), name.capacity()), 600, 600, 20, YELLOW);

		if (name.size() < letterCap)
		{
			DrawText("_", static_cast<int>(textBox.x) + 8 + MeasureText(name.data(), 40), static_cast<int>(textBox.y) + 12, 40, MAROON);
		}
		else
		{
			DrawText("Press BACKSPACE to delete chars...", 600, 650, 20, YELLOW);
		}

		if (name.size() > 0 && name.size() < letterCap)
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
			DrawText(Leaderboard[i].first.data(), 50, 140 + (i * 40), 40, YELLOW);
			DrawText(TextFormat("%i", Leaderboard[i].second), 350, 140 + (i * 40), 40, YELLOW);
		}
	}
}

bool Score::CheckNewHighScore() const noexcept
{
	return (scorepoints >= Leaderboard.back().second);
}

bool Score::InsertNewHighScore()
{
	static constexpr auto isHigher = [](auto& a, auto& b) { return a.second >= b.second; };

	Leaderboard.pop_back();
	Leaderboard.push_back({ name, scorepoints });
	std::ranges::sort(Leaderboard, isHigher);

	return true;
}
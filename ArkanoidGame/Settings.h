#pragma once
#include <string>

namespace ArkanoidGame
{
	class GameWorld
	{
	private:
		GameWorld() = default;

	public:
		static GameWorld& Instance()
		{
			static GameWorld gameWorld;
			return gameWorld;
		}
		
		const std::string GAME_NAME = "ArkanoidGame";
		const std::string RESOURCES_PATH = "Resources/";
		const std::string FONT_PATH = RESOURCES_PATH + "Fonts/Roboto-Regular.ttf";
		const std::string LEVELS_CONFIG_PATH = "levels.txt";
		const std::string LEADERBOARD_FILENAME = "leaderboard.txt";
		const std::string DEFAULT_NAME = "XYZ";
		
		// Size
		const int LEADERBOARD_HEIGHT = 58;
		const int SIZE_LEADERBOARD = 10;
		const int SIZE_MINI_LEADERBOARD = 5;
		const int BORDER_SIZE = 10;
		const float SCREEN_WIDTH = 800.f;
		const float SCREEN_HEIGHT = 600.f;

		const float SIZE_PLATFORM_X = 100.f;
		const float SIZE_PLATFORM_Y = 20.f;
		const float SIZE_BALL = 8.f; // radius ball

		// Brick
		const int BRICK_ROW = 4;
		const int BRICK_COLUMNS = 10;
		const float BRICK_WIDTH = 60.f;
		const float BRICK_HEIGHT = 30.f;
		const float BRICK_SPACING = 8.f; 

		// Variable difficulty
		const int SCORES_PER_APPLE_EASY = 2;
		const int SCORES_PER_APPLE_HARDER_EASY = 4;
		const int SCORES_PER_APPLE_MEDIUM = 6;
		const int SCORES_PER_APPLE_EASIER_HARD = 8;
		const int SCORES_PER_APPLE_HARD = 10;
		
		const float INITIAL_SPEED_EASY = 0.5f;
		const float INITIAL_SPEED_HARDER_EASY = 0.4f;
		const float INITIAL_SPEED_MEDIUM = 0.3f;
		const float INITIAL_SPEED_EASIER_HARD = 0.2f;
		const float INITIAL_SPEED_HARD = 0.1f;
		
		// Other
		const float PAUSE_LENGTH = 1.f;
		const float MOUSE_MOVE_THRESHOLD = 1.f; // Threshold for determining the mouse movement (in pixels)
		const float SPEED_PLATFORM = 400.f; // pixels per second
		const float SPEED_BALL = 300.f; // pixels per second
		const sf::Vector2f INITIAL_DIRECTION_OF_THE_BALL = sf::Vector2f(SPEED_BALL, -SPEED_BALL);
	};
}
#define SETTINGS GameWorld::Instance()


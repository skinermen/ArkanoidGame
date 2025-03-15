#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "UI.h"

struct SLeaderboard
{
	std::string playerName;
	int score;
};

struct SDifficultySettings
{
	std::string nameDifficulty;
	float snakeSpeed;
	int scoresPerApple;
};

namespace ArkanoidGame
{
	class Game;
	enum class GameState;
	
	class Menu : public UI
	{
	public:
		Menu() = default;
		~Menu() override;

		// Get & Set
		std::vector<sf::Text>& GetVTextMainMenuItems() { return vTextMainMenuItems; }
		std::vector<sf::Text>& GetVTextGameOverMenuItems() { return vTextGameOverMenuItems; }
		std::vector<sf::Text>& GetVTextPauseMenuItems() { return vTextPauseMenuItems; }
		std::vector<sf::Text>& GetVTextDifficultyMenuItems() { return vTextDifficultyMenuItems; }
		std::vector<sf::Text>& GetVTextOptionsMenuItems() { return vTextOptionsMenuItems; }
		std::vector<sf::Text>& GetVTextConfirmationMenuItems() { return vTextConfirmationMenuItems; }
		std::vector<SDifficultySettings>& GetVStringDifficultyMenuItems() { return VStringDifficultyMenuItems; }
		std::vector<SLeaderboard>& GetVLeaderboardItems() { return VLeaderboardItems; }
		std::string& GetNameInputPlayerName() { return nameInputPlayerName; }
		sf::Text& GetNameInputMenuText() { return nameInputMenuText; }
		unsigned int GetSelectedItemIndex() const { return selectedItemIndex; }
		
		
		// Init
		void InitPauseTexture() override ;
		void InitMainMenu() override ;
		void InitPauseMenu() override ;
		void InitNameInputMenu() override ;
		void InitConfirmationMenu() override ;
		void InitGameOverMenu() override ;
		void InitGameOverLeaderboardItems();
		void InitDifficultyMenu() override ;
		void InitLeaderboard() override ;
		void InitOptionsMenu() override ;
	
		// Draw
		void DrawMainMenu(sf::RenderWindow& window) override;
		void DrawPauseMenu(sf::RenderWindow& window) override;
		void DrawNameInputMenu(sf::RenderWindow& window) override;
		void DrawConfirmationMenu(sf::RenderWindow& window) override;
		void DrawGameOverMenu(sf::RenderWindow& window) override;
		void DrawLeaderboard(sf::RenderWindow& window) override;
		void DrawDifficultyMenu(sf::RenderWindow& window) override;
		void DrawOptionsMenu(sf::RenderWindow& window) override;
		static void DrawMenuItems(sf::RenderWindow& window, std::vector<sf::Text>& menuItems,
		                          float posX, float posY, float indentation);

		// Service
		void AddRecord(const std::string& playerName, int score);
		void MoveUp(std::vector<sf::Text>& menuItems);
		void MoveDown(std::vector<sf::Text>& menuItems);
		void ResetMenuSelection(std::vector<sf::Text>& menuItems) const;
		void ResetAllMenuSelection();
		static void SaveRecordsToFile(const std::vector<SLeaderboard>& leaderboard, const std::string& filename);
		static void LoadRecordsFromFile(std::vector<SLeaderboard>& leaderboard, const std::string& filename);
		static bool IsNewRecord(const std::vector<SLeaderboard>& leaderboard, int currentScore);
		void SetFillColorRectangle(int selectedIndex, bool option);
		
	private:
		// Main menu
		std::vector<std::string> VStringMainMenuItems
		{
			"START GAME", "DIFFICULTY", "LEADERBOARD", "OPTIONS", "EXIT"
		};
		std::vector<sf::Text> vTextMainMenuItems;
		sf::Text mainMenuTitle;
		sf::Texture mainMenuTexture;
		sf::RectangleShape mainMenuRectangleBackground;
		
		// Pause menu
		std::vector<std::string> VStringPauseMenuItems
		{
			"RESUME", "MAIN MENU"
		};
		std::vector<sf::Text> vTextPauseMenuItems;
		sf::Text pauseMenuTitle;
		sf::RectangleShape pauseMenuRectangleBackground;

		// Name Input Menu
		sf::Text nameInputMenuText;
		std::string nameInputPlayerName;
		sf::RectangleShape nameInputMenuRectangleBackground;

		// Confirmation Menu
		sf::Text confirmationMenuText;
		std::vector<std::string> VStringConfirmationMenuItems
		{
			"No", "Yes"
		};
		std::vector<sf::Text> vTextConfirmationMenuItems;
		sf::RectangleShape confirmationMenuRectangleBackground;
		
		// Game Over menu
		std::vector<std::string> VStringGameOverMenuItems
		{
			"NEW GAME", "MAIN MENU"
		};
		std::vector<sf::Text> vTextGameOverMenuItems;
		std::vector<sf::Text> vTextGameOverLeaderboardItems;
		sf::Text gameOverScoreTitle;
		sf::Text gameOverRecordsTitle;
		sf::RectangleShape gameOverRectangleBackground;

		// Difficulty menu
		std::vector<SDifficultySettings> VStringDifficultyMenuItems
		{
			{"EASY", INITIAL_SPEED_EASY, SCORES_PER_APPLE_EASY},
			{"HARDER EASY", INITIAL_SPEED_HARDER_EASY, SCORES_PER_APPLE_HARDER_EASY},
			{"MEDIUM", INITIAL_SPEED_MEDIUM, SCORES_PER_APPLE_MEDIUM},
			{"EASIER HARD", INITIAL_SPEED_EASIER_HARD, SCORES_PER_APPLE_EASIER_HARD},
			{"HARD", INITIAL_SPEED_HARD, SCORES_PER_APPLE_HARD}
		};
		std::vector<sf::Text> vTextDifficultyMenuItems;
		sf::Text difficultyMenuTitle;
		sf::RectangleShape difficultyMenuRectangleBackground;

		// Leaderboard
		std::vector<SLeaderboard> VLeaderboardItems;
		std::vector<sf::Text> vTextLeaderboardItems;
		sf::RectangleShape leaderboardRectangleBackground;
		sf::Text leaderboardTextTitle;
		sf::Text leaderboardTextInstructions;
		sf::Texture leaderboardTexture;

		// Options
		sf::Text optionsMenuTitle;
		std::vector<std::string> VStringOptionsMenuItems
		{
			{"Sounds"}, {"Music"}
		};
		std::vector<sf::Text> vTextOptionsMenuItems;
		std::vector<sf::RectangleShape> vRectanglesOptionsMenu;
		sf::RectangleShape optionsMenuRectangleBackground;
		
		// Other
		sf::Text limiter;
		unsigned int selectedItemIndex = 0;
		sf::Sprite pauseBlurSprite;
		sf::RenderTexture pauseBlurTexture;
	};

	
}
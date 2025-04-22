#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Platform.h"
#include "Ball.h"
#include "Bricks/BrickManager.h"

namespace ArkanoidGame
{
	class Game
	{
	public:
		Game(sf::RenderWindow& window);
		~Game();

		void Init(sf::RenderWindow& window);
		void Update(float currentTime, sf::RenderWindow& window, const sf::Event& event);
		void Draw(sf::RenderWindow& window);
		static void Shutdown();

		// Get & Set
		Menu& GetMenu() { return menu; }
		int GetIsGameStarting() const { return isGameStarting; }
		void SetIsGameStarting(bool newValue) { isGameStarting = newValue; }
		float GetGameStartTime() const { return gameStartTime; }
		void SetGameStartTime(float newValue) { gameStartTime = newValue; }
		void SetTimeSinceGameOver(float newValue) { timeSinceGameOver = newValue; }
		int GetNumEatenApples() const { return numEatenApples; }
		void SetNumEatenApples(int newValue) { numEatenApples = newValue; }
		int GetScoresPerApple() const { return scoresPerApple; }

	private:
		void InitGameState();
		void InitStartNewGame();
		void UpdatePlayingState(const sf::Event& event, sf::RenderWindow& window, float currentTime);
		void UpdateNameInputMenuState(const sf::Event& event);
		void UpdateMenuState(const sf::Event& event, sf::RenderWindow& window, std::vector<sf::Text>& menuItems);
		void UpdateLeaderboardState(const sf::Event& event);

		void HandleMainMenuSelection(unsigned int selectedIndex, sf::RenderWindow& window);
		void HandlePauseMenuSelection(unsigned int selectedIndex);
		static void HandleConfirmationSelection(unsigned int selectedIndex);
		void HandleGameOverMenuSelection(unsigned int selectedIndex);
		void HandleDifficultyMenuSelection(unsigned int selectedIndex);
		void HandleOptionsMenuSelection(unsigned int selectedIndex);
		
		// Game state variables
		bool isScreenLeaderboard;
		bool isGameStarting;
		float gameStartTime;

		bool onKeyHold;
		bool difficultySelected;

		int numEatenApples;
		int scoresPerApple;
		float timeSinceGameOver;
		float currentSnakeSpeed = INITIAL_SPEED_EASY;
		std::vector<GameState> gameStateStack;

		// Game objects
		Menu menu;
		Platform platform;
		Ball ball;
		BrickManager brickManager;
	};
}

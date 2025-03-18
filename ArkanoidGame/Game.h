#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Platform.h"
#include "Ball.h"

namespace ArkanoidGame
{
	enum class GameState
	{
		None = 0,
		MainMenu,
		Playing,
		NameInputMenu,
		ConfirmationMenu,
		GameOver,
		PauseMenu,
		Leaderboard,
		Difficulty,
		Options,
	};

	class Game
	{
	public:
		Game(sf::RenderWindow& window);
		~Game();

		void Init(sf::RenderWindow& window);
		void Update(float currentTime, sf::RenderWindow& window, const sf::Event& event);
		void Draw(sf::RenderWindow& window);
		static void Shutdown();

		void PushGameState(GameState state);
		void PopGameState();
		void SwitchGameState(GameState newState);

		// Get & Set
		GameState GetCurrentGameState() const;
		GameState GetPreviousGameState() const;
		int GetRandomEmptyCell();
		
		// UI& GetUI() { return ui; }
		Menu& GetMenu() { return menu; }
		int (&GetField())[FIELD_SIZE_X][FIELD_SIZE_Y] { return field; }
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
		void InitField();
		void InitStartNewGame();
		void UpdatePlayingState(const sf::Event& event, sf::RenderWindow& window, float currentTime);
		void UpdateNameInputMenuState(const sf::Event& event);
		void UpdateMenuState(const sf::Event& event, sf::RenderWindow& window, std::vector<sf::Text>& menuItems);
		void UpdateLeaderboardState(const sf::Event& event);

		void HandleMainMenuSelection(unsigned int selectedIndex, sf::RenderWindow& window);
		void HandlePauseMenuSelection(unsigned int selectedIndex);
		void HandleConfirmationSelection(unsigned int selectedIndex);
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
		int field[FIELD_SIZE_X][FIELD_SIZE_Y];

		// Game objects
		Menu menu;
		Platform platform;
		Ball ball;
	};
}
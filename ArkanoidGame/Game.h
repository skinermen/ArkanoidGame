#pragma once
#include <optional>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Snake.h"
#include "Apple.h"
#include "Wall.h"
#include "Menu.h"

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
		void Shutdown();

		void PushGameState(GameState state);
		void PopGameState();
		void SwitchGameState(GameState newState);

		// Get & Set
		GameState GetCurrentGameState();
		GameState GetPreviousGameState();
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
		void UpdatePlayingState(const sf::Event& event, float currentTime);
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
		std::vector<GameState> gameStateStack;
		int field[FIELD_SIZE_X][FIELD_SIZE_Y];

		// Game objects
		Menu menu;
		std::optional<Snake> snake;
		std::optional<Wall> wall;
		std::optional<Apple> apple;
		std::vector<Apple> applesVec;
		std::vector<Wall> wallsVec;

		// Game mode data
		int gameMode;

		// SFML Resources
		sf::Texture snakeTextureHead; 
		sf::Texture snakeTextureBody;
		sf::Texture foodTexture;
		sf::Texture wallTexture;
		sf::Texture noneTexture;
		sf::Texture grassTexture;
		sf::Texture menuTexture;
		sf::Texture scoreboardTexture;
		sf::RenderTexture pauseBlurTexture;
		sf::Sprite pauseBlurSprite;
		sf::Sprite noneSprite;
		sf::Font font;
		sf::SoundBuffer eatFoodBuffer;
		sf::SoundBuffer deathBuffer;
		sf::SoundBuffer winnerBuffer;
		sf::Music musicMainTheme;
		sf::Image icon;

		sf::Event event;
	};
}
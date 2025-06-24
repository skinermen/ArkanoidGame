#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <set>

#include "UI.h"
#include "Platform.h"
#include "Ball.h"
#include "Bricks/BrickManager.h"
#include "GameMemento.h"
#include "Bonuses/BonusManager.h"

namespace ArkanoidGame
{
	// ReSharper disable once CppInconsistentNaming
	class Game
	{
	public:
		Game();
		~Game();

		void Init();
		void Update(float currentTime, sf::RenderWindow& window);
		void HandleEvent(const sf::Event& event);
		void Draw(sf::RenderWindow& window);
		static void ResetGameStartedFlag();
		static void Shutdown(sf::RenderWindow& window);

	private:
		void InitStartNewGame();
		void StartNextLevel();
		void UpdatePlayingState(sf::RenderWindow& window, float deltaTime);
		void HandleCollisions();
		void SaveState();
		void RestoreState();

		int currentLevelIndex = 0;
		float lastUpdateTime = 0.f;
		static bool hasGameStarted;
		std::vector<GameState> gameStateStack;

		// Game objects
		UI ui;
		Platform platform;
		Ball ball;
		BrickManager brickManager;
		BonusManager bonusManager;
		GameMemento savedState;
		std::set<const Brick*> destroyedBricks;
		int lives = SETTINGS.INITIAL_LIVES;
	};
}

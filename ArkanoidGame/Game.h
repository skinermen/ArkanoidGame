#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "UI.h"
#include "Platform.h"
#include "Ball.h"
#include "Bricks/BrickManager.h"

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
		void Draw(sf::RenderWindow& window);
		static void Shutdown(sf::RenderWindow& window);
		void HandleEvent(const sf::Event& event);
		static void ResetGameStartedFlag();

	private:
		void InitStartNewGame();
		void UpdatePlayingState(sf::RenderWindow& window, float deltaTime);
		void HandleCollisions();
		
		float lastUpdateTime = 0.f;
		static bool hasGameStarted;
		std::vector<GameState> gameStateStack;

		// Game objects
		UI ui;
		Platform platform;
		Ball ball;
		BrickManager brickManager;
	};
}

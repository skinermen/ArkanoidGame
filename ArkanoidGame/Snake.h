#pragma once
#include <queue>
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace ArkanoidGame
{
	class Game; // Forward declaration
	
	enum class SnakeDirection
	{
		Right = 0,
		Up,
		Left,
		Down
	};

	class Snake
	{
	public:
		Snake(Game& game);
		void AddOnField(Game& game);
		void Draw(Game& game, sf::RenderWindow& window);
		void Grow(Game& game);
		void HandleInput();
		void Move(Game& game, float currentTime);

		void SetMovementInterval(float newValue) { movementInterval = newValue; }

	private:
		Position2D position;
		float lastUpdateTime = 0.0f; // The time of the last update
		float movementInterval = INITIAL_SPEED_EASY; // Interval between movements (in seconds)
		SnakeDirection direction;
		sf::Sprite spriteHead;
		sf::Sprite spriteBody;
		int snakeLength;
		std::queue<SnakeDirection> directionQueue; // The line of directions
	};
	
}
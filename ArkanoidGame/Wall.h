#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace ArkanoidGame
{
	class Game; // Forward declaration
	
	class Wall
	{
	public:
		Wall(Game& game);
		void AddOnField(Game& game);
		void Draw(Game& game, sf::RenderWindow& window);

	private:
		Position2D position;
		sf::Sprite sprite;
	};
	
}
#include "Apple.h"
#include "Game.h"

namespace ArkanoidGame
{
	Apple::Apple(Game& game)
	{
		sprite.setTexture(game.GetMenu().GetAppleTexture());
		SetSpriteSize(sprite, FOOD_SIZE, FOOD_SIZE);
		sprite.setOrigin(CELL_SIZE / 2.f, CELL_SIZE / 2.f);
	}

	
	void Apple::AddOnField(Game& game)
	{
		int applePos = game.GetRandomEmptyCell();
		if (applePos != -1)
		{
			//
		}
		game.GetField()[applePos / FIELD_SIZE_X][applePos % FIELD_SIZE_X] = FIELD_CELL_TYPE_APPLE;
	}

	void Apple::Draw(Game& game, sf::RenderWindow& window)
	{
		for (int i = 0; i < FIELD_SIZE_X; i++)
		{
			for (int j = 0; j < FIELD_SIZE_Y; j++)
			{
				switch (game.GetField()[i][j])
				{
				case FIELD_CELL_TYPE_APPLE:
					sprite.setPosition(i * CELL_SIZE + BORDER_SIZE + CELL_SIZE / 2.f,
											 j * CELL_SIZE + LEADERBOARD_HEIGHT + BORDER_SIZE + CELL_SIZE / 2.f);
					window.draw(sprite);
					break;
				default:
					break;
				}
			}
		}
	}
}
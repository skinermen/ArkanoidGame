#include "Wall.h"
#include "Game.h"

namespace ArkanoidGame
{
	Wall::Wall(Game& game)
	{
		sprite.setTexture(game.GetMenu().GetWallTexture());
		SetSpriteSize(sprite, WALL_SIZE, WALL_SIZE);
		sprite.setOrigin(CELL_SIZE / 2.f, CELL_SIZE / 2.f);
	}

	void Wall::AddOnField(Game& game)
	{
		// Adding walls around the perimeter
		for (auto& i : game.GetField())
		{
			i[0] = FIELD_CELL_TYPE_WALL;
			i[FIELD_SIZE_Y - 1] = FIELD_CELL_TYPE_WALL;
		}
		for (int j = 1; j < FIELD_SIZE_Y - 1; j++)
		{
			game.GetField()[0][j] = FIELD_CELL_TYPE_WALL;
			game.GetField()[FIELD_SIZE_X - 1][j] = FIELD_CELL_TYPE_WALL;
		}
	}

	void Wall::Draw(Game& game, sf::RenderWindow& window)
	{
		for (int i = 0; i < FIELD_SIZE_X; i++)
		{
			for (int j = 0; j < FIELD_SIZE_Y; j++)
			{
				// Check if the cell is a wall
				if (game.GetField()[i][j] == FIELD_CELL_TYPE_WALL)
				{
					sprite.setPosition(i * CELL_SIZE + BORDER_SIZE + CELL_SIZE / 2.f,
											j * CELL_SIZE + LEADERBOARD_HEIGHT + BORDER_SIZE + CELL_SIZE / 2.f);
					window.draw(sprite);
				}
			}
		}
	}
}

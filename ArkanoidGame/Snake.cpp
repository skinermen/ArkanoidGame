#include "Snake.h"
#include "Game.h"
#include <vector>

namespace ArkanoidGame
{
	Snake::Snake(Game& game)
	{
		// Initialize snake sprite
		spriteHead.setTexture(game.GetMenu().GetSnakeTextureHead());
		spriteBody.setTexture(game.GetMenu().GetSnakeTextureBody());
		SetSpriteSize(spriteHead, SNAKE_SEGMENT_SIZE, SNAKE_SEGMENT_SIZE);
		SetSpriteSize(spriteBody, SNAKE_SEGMENT_SIZE, SNAKE_SEGMENT_SIZE);
		spriteHead.setScale(GetSpriteScale(spriteHead, SNAKE_SEGMENT_SIZE, SNAKE_SEGMENT_SIZE));
		spriteHead.setOrigin(SNAKE_SEGMENT_SIZE / 2.f, SNAKE_SEGMENT_SIZE / 2.f);
		spriteBody.setScale(GetSpriteScale(spriteBody, SNAKE_SEGMENT_SIZE, SNAKE_SEGMENT_SIZE));
		spriteBody.setOrigin(SNAKE_SEGMENT_SIZE / 2.f, SNAKE_SEGMENT_SIZE / 2.f);

		// Initialize snake state
		snakeLength = 4; // Initial length
		direction = SnakeDirection::Right; // Initial direction
		position = { FIELD_SIZE_X / 2, FIELD_SIZE_Y / 2 }; // The center of the field
		lastUpdateTime = 0.f;
		movementInterval = INITIAL_SPEED_EASY;
	}

	// ReSharper disable once CppMemberFunctionMayBeConst
	void Snake::AddOnField(Game& game)
	{
		// Install the snake on the field
		for (int i = 0; i < snakeLength; i++)
		{
			game.GetField()[position.x - i][position.y] = snakeLength - i;
		}
	}

	void Snake::Draw(Game& game, sf::RenderWindow& window)
	{
		// First, draw the head
		for (int i = 0; i < FIELD_SIZE_X; i++)
		{
			for (int j = 0; j < FIELD_SIZE_Y; j++)
			{
				if (game.GetField()[i][j] == snakeLength) // Condition for the head
				{
					spriteHead.setPosition
					(i * CELL_SIZE + BORDER_SIZE + CELL_SIZE / 2.f,
					 j * CELL_SIZE + LEADERBOARD_HEIGHT + BORDER_SIZE + CELL_SIZE / 2.f);
					window.draw(spriteHead);
				}
			}
		}

		// Then we draw the body
		for (int i = 0; i < FIELD_SIZE_X; i++)
		{
			for (int j = 0; j < FIELD_SIZE_Y; j++)
			{
				if (game.GetField()[i][j] > FIELD_CELL_TYPE_NONE && game.GetField()[i][j] < snakeLength)
				{
					spriteBody.setPosition
					(i * CELL_SIZE + BORDER_SIZE + CELL_SIZE / 2.f,
					 j * CELL_SIZE + LEADERBOARD_HEIGHT + BORDER_SIZE + CELL_SIZE / 2.f);
					window.draw(spriteBody);
				}
			}
		}
	}

	void Snake::Grow(Game& game)
	{
		for (auto& i : game.GetField())
		{
			for (int& j : i)
			{
				if (j > FIELD_CELL_TYPE_NONE)
				{
					j++;
				}
			}
		}
	}

	void Snake::HandleInput()
	{
		// We get the last direction that was added to the queue
		SnakeDirection currentDirection = direction;
		if (!directionQueue.empty())
		{
			currentDirection = directionQueue.back();
		}

		// Recording keystrokes
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && currentDirection != SnakeDirection::Left)
		{
			if (directionQueue.empty() || directionQueue.back() != SnakeDirection::Right)
			{
				directionQueue.push(SnakeDirection::Right);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && currentDirection != SnakeDirection::Down)
		{
			if (directionQueue.empty() || directionQueue.back() != SnakeDirection::Up)
			{
				directionQueue.push(SnakeDirection::Up);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && currentDirection != SnakeDirection::Right)
		{
			if (directionQueue.empty() || directionQueue.back() != SnakeDirection::Left)
			{
				directionQueue.push(SnakeDirection::Left);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && currentDirection != SnakeDirection::Up)
		{
			if (directionQueue.empty() || directionQueue.back() != SnakeDirection::Down)
			{
				directionQueue.push(SnakeDirection::Down);
			}
		}

		// Limit the size of the queue if necessary
		while (directionQueue.size() > 3)
		{
			directionQueue.pop();
		}
	}
	
	void Snake::Move(Game& game, float currentTime)
	{
		if (game.GetCurrentGameState() != GameState::Playing)
		{
			return;
		}

		if (game.GetIsGameStarting())
		{
			if (game.GetGameStartTime() == 0.f)
			{
				game.SetGameStartTime(currentTime);
			}
			if (currentTime - game.GetGameStartTime() < PAUSE_LENGTH)
			{
				return;
			}
			game.SetIsGameStarting(false);
		}

	    if (currentTime - lastUpdateTime >= movementInterval)
	    {
	        // Use the following direction from the queue, if there is
	        if (!directionQueue.empty())
	        {
	            SnakeDirection nextDirection = directionQueue.front();
	            directionQueue.pop();

	            // We check that the direction is not opposite to the current
	            if ((direction == SnakeDirection::Up && nextDirection != SnakeDirection::Down) ||
	                (direction == SnakeDirection::Down && nextDirection != SnakeDirection::Up) ||
	                (direction == SnakeDirection::Left && nextDirection != SnakeDirection::Right) ||
	                (direction == SnakeDirection::Right && nextDirection != SnakeDirection::Left))
	            {
	                direction = nextDirection;
	            }
	        }

	        // We move the snakes
	        switch (direction)
	    	{
	            case SnakeDirection::Right:
	                position.x++;
	                if (position.x >= FIELD_SIZE_X) position.x = 0;
	        		spriteHead.setRotation(0);
	                break;
	            case SnakeDirection::Up:
	                position.y--;
	                if (position.y < 0) position.y = FIELD_SIZE_Y - 1;
	        		spriteHead.setRotation(270);
	                break;
	            case SnakeDirection::Left:
	                position.x--;
	                if (position.x < 0) position.x = FIELD_SIZE_X - 1;
	        		spriteHead.setRotation(180);
	                break;
	            case SnakeDirection::Down:
	                position.y++;
	                if (position.y >= FIELD_SIZE_Y) position.y = 0;
	        		spriteHead.setRotation(90);
	                break;
		    }

	    	// Check the collision with a wall || We check the collision with ourselves
	    	if (game.GetField()[position.x][position.y] == FIELD_CELL_TYPE_WALL ||
	    		game.GetField()[position.x][position.y] > FIELD_CELL_TYPE_NONE)
	    	{
	    		game.SetTimeSinceGameOver(0.f);
	    		if (game.GetMenu().IsNewRecord(game.GetMenu().GetVLeaderboardItems(), game.GetMenu().GetNumScores()))
	    		{
	    			game.SwitchGameState(GameState::ConfirmationMenu);
	    		}
			    else
			    {
				    game.SwitchGameState(GameState::GameOver);
			    }
	    		game.GetMenu().PlaySound(game.GetMenu().GetDeathBuffer());
	    		return;
	    	}

	        // Check if the snake has eaten an apple
	        if (game.GetField()[position.x][position.y] == FIELD_CELL_TYPE_APPLE)
	        {
	            snakeLength++;
	        	game.SetNumEatenApples(game.GetNumEatenApples() + 1);
	        	game.GetMenu().GetNumScores() += game.GetScoresPerApple();
	            Grow(game);
	            AddOnField(game);
	            game.GetMenu().PlaySound(game.GetMenu().GetEatAppleBuffer());
	        }

	        // We update the game field
	        game.GetField()[position.x][position.y] = snakeLength + 1;

	        // Reduce the life of the body parts
	        for (auto& i : game.GetField())
	        {
	            for (int& j : i)
	            {
	                if (j > FIELD_CELL_TYPE_NONE)
	                {
		                j--;
	                }
	            }
	        }

	        // We update the time of the last update
	        lastUpdateTime = currentTime;
	    }
	}
}

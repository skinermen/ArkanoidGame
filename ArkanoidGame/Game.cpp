// ReSharper disable CppClangTidyClangDiagnosticCoveredSwitchDefault
#include "Game.h"
#include "Application.h"
#include <cassert>
#include <random>

namespace ArkanoidGame
{
	Game::Game(sf::RenderWindow& window)
		: isScreenLeaderboard(false),
		  isGameStarting(true),
		  gameStartTime(0.f),
		  onKeyHold(false),
		  difficultySelected(false),
		  numEatenApples(0),
		  timeSinceGameOver(0.f),
		  gameMode(0)
	{
		Init(window);
	}

	Game::~Game() = default;

	void Game::Init(sf::RenderWindow& window)
	{
		menu.Init();
		PushGameState(GameState::MainMenu);
		InitGameState();
		InitField();
		window.setIcon(32, 32, menu.GetIcon().getPixelsPtr());
	}

	void Game::InitGameState()
	{
		// Set default value
		menu.SetNumScores(0);

		// Start music if in Playing state
		if (GetCurrentGameState() == GameState::Playing)
		{
			menu.InitPlayMusic();
			menu.OnPlayMusic(true);
		}
	}

	void Game::InitField()
	{
		// Clear the game field
		for (auto& row : field)
		{
			for (int& cell : row)
			{
				cell = FIELD_CELL_TYPE_NONE;
			}
		}
	}

	void Game::InitStartNewGame()
	{
		PushGameState(GameState::Playing);
		InitGameState();
		InitField();
	}
	
	void Game::Update(float currentTime, sf::RenderWindow& window, const sf::Event& event)
	{
		switch (GetCurrentGameState())
		{
		case GameState::Playing:
			UpdatePlayingState(event, window, currentTime);
			break;
		case GameState::NameInputMenu:
			UpdateNameInputMenuState(event);
			break;
		case GameState::ConfirmationMenu:
			UpdateMenuState(event, window, menu.GetVTextConfirmationMenuItems());
			break;
		case GameState::GameOver:
			UpdateMenuState(event, window, menu.GetVTextGameOverMenuItems());
			break;
		case GameState::MainMenu:
			UpdateMenuState(event, window, menu.GetVTextMainMenuItems());
			break;
		case GameState::PauseMenu:
			isGameStarting = true;
			gameStartTime = 0.f;
			UpdateMenuState(event, window, menu.GetVTextPauseMenuItems());
			break;
		case GameState::Leaderboard:
			UpdateLeaderboardState(event);
			break;
		case GameState::Difficulty:
			UpdateMenuState(event, window, menu.GetVTextDifficultyMenuItems());
			break;
		case GameState::Options:
			UpdateMenuState(event, window, menu.GetVTextOptionsMenuItems());
			break;
		case GameState::None:  // NOLINT(bugprone-branch-clone)
				break;
		default:
			break;
		}

		menu.Update(*this);
	}

	void Game::UpdatePlayingState(const sf::Event& event, const sf::RenderWindow& window, float currentTime)
	{
		static float lastTime = currentTime;
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// Update the platform
		platform.Update(window, deltaTime);
		// Update the ball
		ball.Update(deltaTime);

		if (ball.CheckCollisionWithPlatform(platform))
		{
			// We get the boundaries of the platform and its center
			sf::FloatRect platformBounds = platform.GetShape().getGlobalBounds();
			float platformCenterX = platformBounds.left + platformBounds.width / 2.f;
    
			// We calculate the displacement of the blow from the center of the platform (in the range [-1, 1])
			sf::Vector2f ballPos = ball.GetShape().getPosition();
			float offset = (ballPos.x - platformCenterX) / (platformBounds.width / 2.f);
    
			// The new direction of direction: the horizontal component depends on Offset, the vertical is fixed (rebound up)
			sf::Vector2f newDir(offset, -1.f);
			float len = std::sqrt(newDir.x * newDir.x + newDir.y * newDir.y);
			newDir.x /= len;
			newDir.y /= len;
    
			// We retain the current ball speed
			float currentSpeed = std::sqrt(
				ball.GetVelocity().x * ball.GetVelocity().x +
				ball.GetVelocity().y * ball.GetVelocity().y
			);
    
			// We update the speed of the ball with a new direction
			ball.SetVelocity(newDir * currentSpeed);
    
			// Additionally, you can move the ball just above the platform to avoid stuck
			ball.SetPosition(ballPos.x, platformBounds.top - ball.GetShape().getRadius());
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			if (!onKeyHold)
			{
				PushGameState(GameState::PauseMenu);
				onKeyHold = true;
			}
			onKeyHold = true;
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			onKeyHold = false;
		}
	}

	void Game::UpdateNameInputMenuState(const sf::Event& event)
	{
		if (event.type == sf::Event::TextEntered && !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			if (!onKeyHold)
			{
				if (event.text.unicode == '' && !menu.GetNameInputPlayerName().empty()) 
				{
					menu.GetNameInputPlayerName().pop_back();
					onKeyHold = true;
				}
				else if (event.text.unicode < 128 && event.text.unicode != 32 && event.text.unicode != '') // Only ASCII-symbols without Space and Backspace
				{
					menu.GetNameInputPlayerName() += static_cast<char>(event.text.unicode);
					onKeyHold = true;
				}
			}				
			menu.GetNameInputMenuText().setString("Enter your name: " + menu.GetNameInputPlayerName());
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			if (!onKeyHold)
			{
				if (menu.GetNameInputPlayerName().empty())
				{
					menu.GetNameInputPlayerName() = "XYZ";
				}
				menu.AddRecord(menu.GetNameInputPlayerName(), menu.GetNumScores());
				PushGameState(GameState::GameOver);
				onKeyHold = true;
			}
		}
		
		if (event.type == sf::Event::KeyReleased)
		{
			onKeyHold = false;
		}
	}
	
	void Game::UpdateMenuState(const sf::Event& event, sf::RenderWindow& window, std::vector<sf::Text>& menuItems)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if (!onKeyHold)
			{
				menu.MoveUp(menuItems);
				menu.PlaySound(menu.GetSelectMenuBuffer());
			}
			onKeyHold = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (!onKeyHold)
			{
				menu.MoveDown(menuItems);
				menu.PlaySound(menu.GetSelectMenuBuffer());
			}
			onKeyHold = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			if (!onKeyHold)
			{
				switch (GetCurrentGameState())  // NOLINT(clang-diagnostic-switch-enum)
				{
				case GameState::MainMenu:
					HandleMainMenuSelection(menu.GetSelectedItemIndex(), window);
					break;
				case GameState::PauseMenu:
					HandlePauseMenuSelection(menu.GetSelectedItemIndex());
					break;
				case GameState::ConfirmationMenu:
					HandleConfirmationSelection(menu.GetSelectedItemIndex());
					break;
				case GameState::GameOver:
					HandleGameOverMenuSelection(menu.GetSelectedItemIndex());
					break;
				case GameState::Difficulty:
					HandleDifficultyMenuSelection(menu.GetSelectedItemIndex());
					break;
				case GameState::Options:
					HandleOptionsMenuSelection(menu.GetSelectedItemIndex());
						break;
				default:
					break;
				}
				menu.PlaySound(menu.GetPressEnterBuffer());
				onKeyHold = true;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) && GetCurrentGameState() != GameState::MainMenu)
		{
			if (!onKeyHold)
			{
				SwitchGameState(GetPreviousGameState());
			}
			onKeyHold = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) && GetCurrentGameState() == GameState::MainMenu)
		{
			if (!onKeyHold)
			{
				window.close();
			}
			onKeyHold = true;
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			onKeyHold = false;
		}
	}

	void Game::UpdateLeaderboardState(const sf::Event& event)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		{
			if (!onKeyHold)
			{
				SwitchGameState(GetPreviousGameState());
			}
			onKeyHold = true;
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			onKeyHold = false;
		}
	}
	
	void Game::HandleMainMenuSelection(unsigned int selectedIndex, sf::RenderWindow& window)
	{
		switch (selectedIndex)
		{
		case 0:  // Start Game
			InitStartNewGame();
			break;
		case 1:  // Difficulty
			menu.ResetAllMenuSelection();
			PushGameState(GameState::Difficulty);
			break;
		case 2:  // Leaderboard
			PushGameState(GameState::Leaderboard);
			break;
		case 3:  // Options
			PushGameState(GameState::Options);
				break;
		default: // Exit
			window.close();
			break;
		}
	}

	void Game::HandlePauseMenuSelection(unsigned int selectedIndex)
	{
		switch (selectedIndex)  // NOLINT(hicpp-multiway-paths-covered)
		{
		case 0:  // Continue Game
			SwitchGameState(GameState::Playing);
			menu.OnPlayMusic(true);
			break;
		default:  // Back to main menu
			menu.ResetAllMenuSelection();
			PushGameState(GameState::MainMenu);
			break;
		}
	}

	void Game::HandleConfirmationSelection(unsigned int selectedIndex)
	{
		switch (selectedIndex)  // NOLINT(hicpp-multiway-paths-covered)
		{
		case 0:  // No
			PushGameState(GameState::GameOver);
			break;
		default: // Yes
			PushGameState(GameState::NameInputMenu);
			break;
		}
	}

	void Game::HandleGameOverMenuSelection(unsigned int selectedIndex)
	{
		switch (selectedIndex)  // NOLINT(hicpp-multiway-paths-covered)
		{
		case 0:  // New Game
			InitStartNewGame();
			break;
		default:  // Back to main menu
			menu.ResetAllMenuSelection();
			PushGameState(GameState::MainMenu);
			break;
		}
	}

	void Game::HandleDifficultyMenuSelection(unsigned int selectedIndex)
	{
		// ReSharper disable once CppUnsignedZeroComparison
		if (selectedIndex < menu.GetVStringDifficultyMenuItems().size())
		{
			currentSnakeSpeed = menu.GetVStringDifficultyMenuItems()[selectedIndex].snakeSpeed;
			scoresPerApple = menu.GetVStringDifficultyMenuItems()[selectedIndex].scoresPerApple;
			difficultySelected = true;
		
			SwitchGameState(GameState::MainMenu);
		}
	}

	void Game::HandleOptionsMenuSelection(unsigned int selectedIndex)
	{
		switch (selectedIndex)  // NOLINT(hicpp-multiway-paths-covered)
		{
		case 0:  // Sound
			menu.SwitchIsSoundOn();
			menu.SetFillColorRectangle(selectedIndex, menu.GetIsSoundOn());
			break;
		default:  // Music
			menu.SwitchIsMusicOn();
			menu.SetFillColorRectangle(selectedIndex, menu.GetIsMusicOn());
			break;
		}
	}

	void Game::Draw(sf::RenderWindow& window)
	{		
		// Draw Background
		for (int i = 0; i < FIELD_SIZE_X; i++)
		{
			for (int j = 0; j < FIELD_SIZE_Y; j++)
			{
				if (field[i][j] == FIELD_CELL_TYPE_NONE)
				{
					sf::Sprite& noneSprite = menu.GetNoneSprite();
					noneSprite.setPosition(i * CELL_SIZE + BORDER_SIZE + CELL_SIZE / 2.f,
											 j * CELL_SIZE + LEADERBOARD_HEIGHT + BORDER_SIZE + CELL_SIZE / 2.f);
					window.draw(noneSprite);
				}
			}
		}
		
		// Draw Platform
		platform.Draw(window);

		// Draw Ball
		ball.Draw(window);
		
		// Draw UI
		menu.Draw(window);
	}

	void Game::Shutdown()
	{
	}

	void Game::PushGameState(GameState state)
	{
		menu.ResetAllMenuSelection();
		gameStateStack.push_back(state);
	}

	void Game::PopGameState()
	{
		if (!gameStateStack.empty())
		{
			menu.ResetAllMenuSelection();
			gameStateStack.pop_back();
		}
		else
		{
			menu.ResetAllMenuSelection();
			gameStateStack.push_back(GameState::MainMenu);
		}
	}

	void Game::SwitchGameState(GameState newState)
	{
		if (!gameStateStack.empty())
		{
			menu.ResetAllMenuSelection();
			gameStateStack.pop_back();
			gameStateStack.push_back(newState);
		}
		else
		{
			PushGameState(newState);
		}
	}

	GameState Game::GetCurrentGameState() const
	{
		if (!gameStateStack.empty())
		{
			return gameStateStack.back();
		}
		else
		{
			return GameState::None;
		}
	}

	GameState Game::GetPreviousGameState() const
	{
		if (gameStateStack.size() > 1)
		{
			return gameStateStack.end()[-2];
		}
		else
		{
			return GameState::None;
		}
	}
	
	int Game::GetRandomEmptyCell()
	{
		int emptyCellCount = 0;
		for (const auto& i : field)
		{
			for (int j : i)
			{
				if (j == FIELD_CELL_TYPE_NONE)
				{
					emptyCellCount++;
				}
			}
		}
		int targetEmptyCellIndex = rand() % emptyCellCount;
		int emptyCellIndex = 0;
		for (int i = 0; i < FIELD_SIZE_X; i++)
		{
			for (int j = 0; j < FIELD_SIZE_Y; j++)
			{
				if (field[i][j] == FIELD_CELL_TYPE_NONE)
				{
					if (emptyCellIndex == targetEmptyCellIndex)
					{
						return i * FIELD_SIZE_Y + j;
					}
					emptyCellIndex++;
				}
			}
		}
		return -1;
	}

	void Shutdown()
	{
		
	}
}


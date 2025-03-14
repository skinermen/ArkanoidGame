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
		  scoresPerApple(10),
		  timeSinceGameOver(0.f),
		  gameMode(0)
	{
		Init(window);
	}

	Game::~Game()
	{
	}

	void Game::Init(sf::RenderWindow& window)
	{
		menu.Init();
		PushGameState(GameState::MainMenu);
		InitGameState();
		InitField();
		// window.setIcon(32, 32, icon.getPixelsPtr());
	}

	void Game::InitGameState()
	{
		// Set default value
		menu.SetNumScores(0);

		// Init Player
		snake = Snake(*this);
		
		// Init Walls
		wallsVec.clear();
		wall = Wall(*this);
		wallsVec.emplace_back(wall.value());
		
		// Init Apples
		applesVec.clear();
		apple = Apple(*this);
		applesVec.emplace_back(apple.value());

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

		// Add game objects to the field
		snake->AddOnField(*this);
		wall->AddOnField(*this);
		apple->AddOnField(*this);
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
			UpdatePlayingState(event, currentTime);
			break;
		case GameState::NameInputMenu:
			UpdateNameInputMenuState(event);
			break;
		case GameState::ConfirmationMenu:
			UpdateMenuState(event, window, menu.GetVTextMainMenuItems());
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

	void Game::UpdatePlayingState(const sf::Event& event, float currentTime)
	{
		snake->HandleInput();
		snake->Move(*this, currentTime);

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
		if (selectedIndex >= 0 && selectedIndex < menu.GetVStringDifficultyMenuItems().size())
		{
			snake->SetMovementInterval(menu.GetVStringDifficultyMenuItems()[selectedIndex].snakeSpeed);
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
				switch (field[i][j])
				{
				case FIELD_CELL_TYPE_NONE:
					menu.GetNoneSprite().setPosition
					( i * CELL_SIZE + BORDER_SIZE + CELL_SIZE / 2.f,
					  j * CELL_SIZE + LEADERBOARD_HEIGHT + BORDER_SIZE + CELL_SIZE / 2.f);
					window.draw(menu.GetNoneSprite());
					break;
				default:
					break;
				}
			}
		}
		
		// Draw Player
		snake->Draw(*this, window);

		// Draw Food
		for (Apple& apple : applesVec)
		{
			apple.Draw(*this, window);
		}
		
		// Draw Barrier
		for (Wall& wall : wallsVec)
		{
			wall.Draw(*this, window);
		}

		// Draw UI
		menu.Draw(window);
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

	GameState Game::GetCurrentGameState()
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

	GameState Game::GetPreviousGameState()
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
						return  i * FIELD_SIZE_X + j;
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


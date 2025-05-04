// ReSharper disable CppClangTidyClangDiagnosticCoveredSwitchDefault
#include "Game.h"
#include "Application.h"
#include "GameState.h"
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
		  timeSinceGameOver(0.f)

	{
		Init(window);
	}

	Game::~Game() = default;

	void Game::Init(sf::RenderWindow& window)
	{
		menu.Init();
		GameStateManager::Instance().SwitchState(GameState::MainMenu);
		InitGameState();
		window.setIcon(32, 32, menu.GetIcon().getPixelsPtr());
	}

	void Game::InitGameState()
	{
		menu.SetNumScores(0);
		menu.InitPlayMusic();
		menu.UpdatePlayMusic();
	}

	void Game::InitStartNewGame()
	{
		brickManager.Init();
		ball.Reset();
		platform.SetPosition(sf::Vector2f(SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEIGHT - 50.f));
		GameStateManager::Instance().PushState(GameState::Playing);
		InitGameState();
	}

	void Game::Update(float currentTime, sf::RenderWindow& window, const sf::Event& event)
	{
		switch (GameStateManager::Instance().GetCurrentState())
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
		case GameState::Winner:
			UpdateMenuState(event, window, menu.GetVTextGameOverMenuItems());
			break;
		case GameState::None:  // NOLINT(bugprone-branch-clone)
				break;
		default:
			break;
		}

		menu.Update();
	}

	void Game::UpdatePlayingState(const sf::Event& event, sf::RenderWindow& window, float currentTime)
	{
		static float lastTime = currentTime;
		float deltaTime = currentTime - lastTime;
		if (deltaTime > 0.1f)
		{
			deltaTime = 0.016f;
		}
		lastTime = currentTime;
		
		platform.Update(window, deltaTime);
		ball.Update(window, deltaTime);
		brickManager.Update();
		if (GameStateManager::Instance().GetCurrentState() != GameState::Playing)
		{
			menu.UpdatePlayMusic();
		}
		
		ball.CollisionHandlingWithObjects(platform, brickManager.GetBricks());

		if (ball.GetPosition().y - ball.GetShape().getRadius() > SETTINGS.SCREEN_HEIGHT)
		{
			GameStateManager::Instance().PushState(GameState::GameOver);
			menu.UpdatePlayMusic();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			if (!onKeyHold)
			{
				GameStateManager::Instance().PushState(GameState::PauseMenu);
				menu.UpdatePlayMusic();
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
				GameStateManager::Instance().PushState(GameState::GameOver);
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
				switch (GameStateManager::Instance().GetCurrentState())  // NOLINT(clang-diagnostic-switch-enum)
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
				case GameState::Winner:
					HandleGameOverMenuSelection(menu.GetSelectedItemIndex());
					break;
				default:
					break;
				}
				menu.PlaySound(menu.GetPressEnterBuffer());
				onKeyHold = true;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) && GameStateManager::Instance().GetCurrentState() != GameState::MainMenu)
		{
			if (!onKeyHold)
			{
				menu.ResetAllMenuSelection();
				GameStateManager::Instance().PopState();
				menu.UpdatePlayMusic();
			}
			onKeyHold = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) && GameStateManager::Instance().GetCurrentState() == GameState::MainMenu)
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
				GameStateManager::Instance().SwitchState(GameStateManager::Instance().GetPreviousState());
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
			GameStateManager::Instance().PushState(GameState::Difficulty);
			break;
		case 2:  // Leaderboard
			GameStateManager::Instance().PushState(GameState::Leaderboard);
			break;
		case 3:  // Options
			menu.ResetAllMenuSelection();
			GameStateManager::Instance().PushState(GameState::Options);
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
			GameStateManager::Instance().PopState();
			menu.UpdatePlayMusic();
			break;
		default:  // Back to main menu
			menu.ResetAllMenuSelection();
			GameStateManager::Instance().ClearStates();
			GameStateManager::Instance().PushState(GameState::MainMenu);
			break;
		}
	}

	void Game::HandleConfirmationSelection(unsigned int selectedIndex)
	{
		switch (selectedIndex)  // NOLINT(hicpp-multiway-paths-covered)
		{
		case 0:  // No
			GameStateManager::Instance().PushState(GameState::GameOver);
			break;
		default: // Yes
			GameStateManager::Instance().PushState(GameState::NameInputMenu);
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
			GameStateManager::Instance().PushState(GameState::MainMenu);
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
		
			GameStateManager::Instance().SwitchState(GameState::MainMenu);
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
		platform.Draw(window);
		ball.Draw(window);
		brickManager.Draw(window);
		menu.Draw(window);
	}

	void Game::Shutdown()
	{
	}

	void Shutdown()
	{
		
	}
}


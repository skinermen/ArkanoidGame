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
		GameStateManager::Instance().PushState(GameState::MainMenu);
		InitGameState();
		window.setIcon(32, 32, menu.GetIcon().getPixelsPtr());
	}

	void Game::InitGameState()
	{
		// Set default value
		menu.SetNumScores(0);

		// Start music if in Playing state
		if (GameStateManager::Instance().GetCurrentState() == GameState::Playing)
		{
			menu.InitPlayMusic();
			menu.OnPlayMusic(true);
		}
	}

	void Game::InitStartNewGame()
	{
		// Например, сбросьте игру, переместите шарик, платформу и т.д.
		ball.Reset();
		platform.SetPosition(sf::Vector2f(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 50.f));

		// Генерируем кирпичи для уровня
		InitBricks();
		
		GameStateManager::Instance().PushState(GameState::Playing);
		InitGameState();
	}

	void Game::InitBricks()
	{
		bricks.clear();
    
		const int rows = 5;
		const int columns = 10;
    
		// Размер кирпича
		const float brickWidth = 60.f;
		const float brickHeight = 20.f;
		// Отступ между кирпичами
		const float spacing = 5.f; 
    
		// Вычисляем общую ширину сетки, учитывая отступы между колонками
		float totalWidth = columns * brickWidth + (columns - 1) * spacing;
		float startX = (SCREEN_WIDTH - totalWidth) / 2.f + brickWidth / 2.f;
		float startY = 50.f;
    
		// Настраиваем генератор случайных чисел
		static std::random_device rd;
		static std::mt19937 gen(rd());
		// Диапазон для каналов цвета: [0..255]
		std::uniform_int_distribution<int> distColor(0, 255);
    
		for (int row = 0; row < rows; ++row)
		{
			for (int col = 0; col < columns; ++col)
			{
				float x = startX + col * (brickWidth + spacing);
				float y = startY + row * (brickHeight + spacing);
            
				// Генерируем случайный цвет
				sf::Color randomColor(
					distColor(gen),  // R
					distColor(gen),  // G
					distColor(gen)   // B
				);
            
				// Создаём кирпич
				bricks.push_back(std::make_unique<Brick>(
					sf::Vector2f(x, y),
					sf::Vector2f(brickWidth, brickHeight),
					randomColor
				));
			}
		}
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
		case GameState::None:  // NOLINT(bugprone-branch-clone)
				break;
		default:
			break;
		}

		menu.Update(*this);
	}

	void Game::UpdatePlayingState(const sf::Event& event, sf::RenderWindow& window, float currentTime)
	{
		static float lastTime = currentTime;
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		
		platform.Update(window, deltaTime);
		ball.Update(window, deltaTime);
		
		for (auto& brick : bricks)
		{
			// Если кирпич не разрушен и происходит столкновение
			if (!brick->IsDestroyed() && ball.CheckCollisionWithBrick(*brick))
			{
				// Вычисляем центр кирпича
				sf::FloatRect brickBounds = brick->GetBounds();
				sf::Vector2f brickCenter(brickBounds.left + brickBounds.width / 2.f,
										  brickBounds.top + brickBounds.height / 2.f);
    
				sf::Vector2f ballPos = ball.GetPosition();
				float radius = ball.GetShape().getRadius();
    
				// Вычисляем разницу между центрами
				float dx = ballPos.x - brickCenter.x;
				float dy = ballPos.y - brickCenter.y;
    
				// "Полуразмеры" для расчёта пересечения: половина размеров кирпича плюс радиус шарика
				float combinedHalfWidth = (brickBounds.width / 2.f) + radius;
				float combinedHalfHeight = (brickBounds.height / 2.f) + radius;
    
				// Вычисляем пересечения по каждой оси
				float overlapX = combinedHalfWidth - std::abs(dx);
				float overlapY = combinedHalfHeight - std::abs(dy);
    
				// Разрушаем кирпич
				brick->Destroy();
    
				// Если пересечение по X меньше, значит контакт произошёл по боковой стороне
				if (overlapX < overlapY)
				{
					// Инвертируем горизонтальную составляющую
					ball.SetVelocity(sf::Vector2f(-ball.GetVelocity().x, ball.GetVelocity().y));
					// Корректируем позицию шарика так, чтобы он не застревал
					if (dx > 0)
						ball.SetPosition(sf::Vector2f(brickBounds.left + brickBounds.width + radius, ballPos.y));
					else
						ball.SetPosition(sf::Vector2f(brickBounds.left - radius, ballPos.y));
				}
				else // Иначе, столкновение по вертикали
				{
					// Инвертируем вертикальную составляющую
					ball.SetVelocity(sf::Vector2f(ball.GetVelocity().x, -ball.GetVelocity().y));
					// Корректируем позицию шарика
					if (dy > 0)
						ball.SetPosition(sf::Vector2f(ballPos.x, brickBounds.top + brickBounds.height + radius));
					else
						ball.SetPosition(sf::Vector2f(ballPos.x, brickBounds.top - radius));
				}
			}
		}
		
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
			ball.SetPosition(sf::Vector2f(ballPos.x, platformBounds.top - ball.GetShape().getRadius()));
		}

		if (ball.GetPosition().y - ball.GetShape().getRadius() > SCREEN_HEIGHT)
		{
			// Переключаем состояние игры на "Game Over"
			GameStateManager::Instance().PushState(GameState::GameOver);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			if (!onKeyHold)
			{
				GameStateManager::Instance().PushState(GameState::PauseMenu);
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
				GameStateManager::Instance().SwitchState(GameStateManager::Instance().GetPreviousState());
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
			GameStateManager::Instance().SwitchState(GameState::Playing);
			menu.OnPlayMusic(true);
			break;
		default:  // Back to main menu
			menu.ResetAllMenuSelection();
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
		for (const auto& brick : bricks)
		{
			brick->Draw(window);
		}
		
		menu.Draw(window);
	}

	void Game::Shutdown()
	{
	}

	void Shutdown()
	{
		
	}
}


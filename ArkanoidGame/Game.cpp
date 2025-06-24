#include <random>

#include "Game.h"
#include "Application.h"
#include "GameState.h"
#include "Bonuses/BonusManager.h"
#include "Bonuses/FireBallBonus.h"
#include "Bonuses/FragileBlocksBonus.h"
#include "Bonuses/PlatformSizeBonus.h"
#include "PlatformCommand.h"

namespace ArkanoidGame
{
	Game::Game() { Init(); } 
	Game::~Game() = default;

	bool Game::hasGameStarted = false;
	void Game::ResetGameStartedFlag() { hasGameStarted = false; }

	void Game::Init()
	{
		ui.Init();
		ui.SetNextLevelCallback([this]() { StartNextLevel(); });
		hasGameStarted = false;
		STATES.SwitchState(GameState::MainMenu);
	}

	void Game::InitStartNewGame()
	{
		brickManager.ResetScore();
		brickManager.Init(0);
		ball.Reset();
		platform.SetPosition(sf::Vector2f(SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEIGHT - 50.f));
		platform.ResetSize();
		lives = SETTINGS.INITIAL_LIVES;
		ui.UpdateLives(lives);
		bonusManager.Clear();
		destroyedBricks.clear();
		SaveState();
	}

	void Game::StartNextLevel()
	{
		++currentLevelIndex;
		if (currentLevelIndex >= brickManager.GetTotalLevels())
		{
			currentLevelIndex = 0; // Or you can complete the game
		}
		brickManager.Init(currentLevelIndex);
		ball.Reset();
		platform.SetPosition(sf::Vector2f(SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEIGHT - 50.f));
		platform.ResetSize();
		lives = SETTINGS.INITIAL_LIVES;
		ui.UpdateLives(lives);
		bonusManager.Clear();
		destroyedBricks.clear();
		SaveState();
	}

	void Game::Update(float currentTime, sf::RenderWindow& window)
	{
		GameState currentState = STATES.GetCurrentState();
		GameState previousState = STATES.GetPreviousState();
	
		if (currentState == GameState::Exit)
			{ Shutdown(window); return; }

		if (currentState == GameState::MainMenu)
			{ hasGameStarted = false; }

		if (currentState == GameState::Playing && !hasGameStarted)
		{
			InitStartNewGame();
			lastUpdateTime = currentTime;
			hasGameStarted = true;
		}
		else if (currentState == GameState::Playing && previousState == GameState::PauseMenu)
			{ lastUpdateTime = currentTime; }

		float deltaTime = currentTime - lastUpdateTime;
		lastUpdateTime = currentTime;

		if (currentState == GameState::Playing)
			{ UpdatePlayingState(window, deltaTime); }
	}

	void Game::UpdatePlayingState(sf::RenderWindow& window, float deltaTime)
	{
		if (ball.GetVelocity().y <= 0 &&
				ball.GetPosition().y - ball.GetShape().getRadius() <= SETTINGS.SCREEN_HEIGHT)
		{
			SaveState();
		}

		platform.Update(window, deltaTime);
		ball.Update(window, deltaTime);
		brickManager.Update();
		HandleCollisions();
		bonusManager.Update(window, deltaTime, platform, ball);

		ui.UpdateScore(brickManager.GetScore());
		ui.UpdateLives(lives);

		if (ball.GetPosition().y - ball.GetShape().getRadius() > SETTINGS.SCREEN_HEIGHT)
		{
			--lives;
			if (lives > 0)
			{
				RestoreState();
				ui.UpdateLives(lives);
				return;
			}
			ui.HandleGameOver(brickManager.GetScore());
			return;
		}

		if (brickManager.AllBricksDestroyed())
		{
			STATES.PushState(GameState::Winner);
			ui.SetScoreForState(GameState::Winner, brickManager.GetScore());
		}
	}
	
	void Game::HandleEvent(const sf::Event& event)
	{
		switch (STATES.GetCurrentState())
		{
		case GameState::MainMenu:
		case GameState::PauseMenu:
		case GameState::GameOver:
		case GameState::Options:
		case GameState::Winner:
		case GameState::ConfirmationMenu:
		case GameState::NameInputMenu:
		ui.HandleEvent(event);
			break;

		case GameState::Playing:
			if (event.key.code == sf::Keyboard::P)
			{
				STATES.PushState(GameState::PauseMenu);
				ui.ResetSelectionForState(GameState::PauseMenu);
			}
			break;
			
		case GameState::Leaderboard:
			if (event.key.code == sf::Keyboard::B)
			{
				STATES.SwitchState(GameState::MainMenu);
				ui.ResetSelectionForState(GameState::Leaderboard);
			}
			break;
			
		default:
			break;
		}
	}

	void Game::HandleCollisions()
	{
		int points = ball.CollisionHandlingWithObjects(platform, brickManager.GetBricks());
		brickManager.AddScore(points);

		static std::default_random_engine eng(std::random_device{}());
		static std::uniform_real_distribution<float> dist(0.f, 1.f);

		for (const auto& brick : brickManager.GetBricks())
		{
			if (brick->IsDestroyed() && destroyedBricks.insert(brick.get()).second)
			{
				if (dist(eng) <= 0.1f)
				{
					float r = dist(eng);
					if (r < 0.33f)
						bonusManager.SpawnBonus(std::make_unique<FireBallBonus>(brick->GetPosition()));
					else if (r < 0.66f)
						bonusManager.SpawnBonus(std::make_unique<FragileBlocksBonus>(brick->GetPosition(), brickManager));
					else if (r < 0.83f)
						bonusManager.SpawnBonus(std::make_unique<PlatformSizeBonus>(brick->GetPosition(),
								std::make_unique<IncreaseSizeCommand>(1.5f, SETTINGS.PLATFORM_BONUS_DURATION)));
					else
						bonusManager.SpawnBonus(std::make_unique<PlatformSizeBonus>(brick->GetPosition(),
								std::make_unique<DecreaseSizeCommand>(0.75f, SETTINGS.PLATFORM_BONUS_DURATION)));
				}
			}
		}
	}

	void Game::SaveState()
	{
		savedState.bricks.clear();
		for (const auto& brick : brickManager.GetBricks())
			savedState.bricks.push_back(brick->Clone());
		savedState.ballPosition = ball.GetPosition();
		savedState.ballVelocity = ball.GetVelocity();
		savedState.platformPosition = platform.GetPosition();
		savedState.score = brickManager.GetScore();
		savedState.currentLevel = currentLevelIndex;
	}

	void Game::RestoreState()
	{
		brickManager.SetBricks(savedState.bricks);
		brickManager.SetScore(savedState.score);
		ball.SetPosition(savedState.ballPosition);
		ball.SetVelocity(savedState.ballVelocity);
		platform.SetPosition(savedState.platformPosition);
		currentLevelIndex = savedState.currentLevel;
		destroyedBricks.clear();
		for (const auto& brick : brickManager.GetBricks())
			if (brick->IsDestroyed())
				destroyedBricks.insert(brick.get());
	}

	void Game::Draw(sf::RenderWindow& window)
	{		
		platform.Draw(window);
		ball.Draw(window);
		brickManager.Draw(window);
		bonusManager.Draw(window);
		ui.Draw(window);
	}

	void Game::Shutdown(sf::RenderWindow& window)
	{
		window.close();
	}
}


#include "Game.h"
#include "Application.h"
#include "GameState.h"
#include <random>

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
		platform.Update(window, deltaTime);
		ball.Update(window, deltaTime);
		brickManager.Update();

		HandleCollisions();

		ui.UpdateScore(brickManager.GetScore());
		if (ball.GetPosition().y - ball.GetShape().getRadius() > SETTINGS.SCREEN_HEIGHT)
		{
			STATES.PushState(GameState::GameOver);
			ui.SetScoreForState(GameState::GameOver, brickManager.GetScore());
		}

		if (brickManager.AllBricksDestroyed())
		{
			STATES.PushState(GameState::Winner);
			ui.SetScoreForState(GameState::Winner, brickManager.GetScore());
		}
		
		if (ball.GetPosition().y - ball.GetShape().getRadius() > SETTINGS.SCREEN_HEIGHT)
		{
			ui.HandleGameOver(brickManager.GetScore());
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
	}

	void Game::Draw(sf::RenderWindow& window)
	{		
		platform.Draw(window);
		ball.Draw(window);
		brickManager.Draw(window);
		ui.Draw(window);
	}

	void Game::Shutdown(sf::RenderWindow& window)
	{
		window.close();
	}
}


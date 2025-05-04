#include <string>
#include <random>
#include <cassert>
#include "UI.h"
#include "Game.h"
#include "Math.h"
#include "GameState.h"

namespace ArkanoidGame
{
	void UI::InitText(sf::Text& text, const sf::Font& font, int size, int style, sf::Color color, const std::string& name)
	{
		text.setFont(font);
		text.setCharacterSize(size);
		text.setStyle(style);
		text.setFillColor(color);
		text.setString(name);
		text.setOrigin(GetTextOrigin(text));
	}

	void UI::InitRectangle(sf::RectangleShape& rectangle, float sizeX, float sizeY, sf::Color fillColor, sf::Color outlineColor, float outlineThickness)
	{
		rectangle.setSize(sf::Vector2f(sizeX, sizeY));
		rectangle.setOrigin(rectangle.getSize().x / 2.f, rectangle.getSize().y / 2.f);
		rectangle.setFillColor(fillColor);
		rectangle.setOutlineColor(outlineColor);
		rectangle.setOutlineThickness(outlineThickness);
	}

	void UI::InitResources()
	{
		assert(font.loadFromFile(SETTINGS.RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));
		assert(snakeTextureHead.loadFromFile(SETTINGS.RESOURCES_PATH + "snake_head.png"));
		assert(snakeTextureBody.loadFromFile(SETTINGS.RESOURCES_PATH + "snake_body.png"));
		assert(appleTexture.loadFromFile(SETTINGS.RESOURCES_PATH + "apple.png"));
		assert(wallTexture.loadFromFile(SETTINGS.RESOURCES_PATH + "wall.png"));
		assert(icon.loadFromFile(SETTINGS.RESOURCES_PATH + "icon.png"));
		assert(deathBuffer.loadFromFile(SETTINGS.RESOURCES_PATH + "Death.wav"));
		assert(eatAppleBuffer.loadFromFile(SETTINGS.RESOURCES_PATH + "Collision.wav"));
		assert(pressEnterBuffer.loadFromFile(SETTINGS.RESOURCES_PATH + "Press_Enter.wav"));
		assert(selectMenuBuffer.loadFromFile(SETTINGS.RESOURCES_PATH + "Select_Menu.wav"));
		assert(musicMainTheme.openFromFile(SETTINGS.RESOURCES_PATH + "MainTheme.wav"));
	}

	void UI::Init()
	{
		InitResources();
		InitPauseTexture();
		
		// Playing Resources
		InitRectangle(playingRectangle, SETTINGS.SCREEN_WIDTH - 20.f, SETTINGS.SCREEN_HEIGHT - 20.f,
			sf::Color::Transparent, sf::Color::White, 10.f);
		
		InitText(playingScoreText, font, 24, 0, sf::Color::White);
		
		InitMainMenu();
		InitPauseMenu();
		InitNameInputMenu();
		InitConfirmationMenu();
		InitLeaderboard();
		InitGameOverMenu();
		InitDifficultyMenu();
		InitOptionsMenu();
		InitWinnerMenu();
	}

	void UI::Update()
	{
		playingScoreText.setString("Scores: " + std::to_string(numScores));
		gameOverScores.setString(std::to_string(numScores));
		isGameOverMenuTextVisible = GameStateManager::Instance().GetCurrentState() == GameState::GameOver;

		isPlayingTextVisible = false;
		isMainMenuTextVisible = false;
		isPauseMenuTextVisible = false;
		isNameInputMenuTextVisible = false;
		isConfirmationMenuTextVisible = false;
		isGameOverMenuTextVisible = false;
		isDifficultyMenuTextVisible = false;
		isScoreboardMenuVisible = false;
		isOptionsMenuTextVisible = false;
		isWinnerMenuTextVisible = false;

		if (GameStateManager::Instance().GetCurrentState() == GameState::Playing) isPlayingTextVisible = true;
		if (GameStateManager::Instance().GetCurrentState() == GameState::MainMenu) isMainMenuTextVisible = true;
		if (GameStateManager::Instance().GetCurrentState() == GameState::PauseMenu) isPauseMenuTextVisible = true;
		if (GameStateManager::Instance().GetCurrentState() == GameState::NameInputMenu) isNameInputMenuTextVisible = true;
		if (GameStateManager::Instance().GetCurrentState() == GameState::ConfirmationMenu) isConfirmationMenuTextVisible = true;
		if (GameStateManager::Instance().GetCurrentState() == GameState::GameOver) isGameOverMenuTextVisible = true;
		if (GameStateManager::Instance().GetCurrentState() == GameState::Difficulty) isDifficultyMenuTextVisible = true;
		if (GameStateManager::Instance().GetCurrentState() == GameState::Leaderboard) isScoreboardMenuVisible = true;
		if (GameStateManager::Instance().GetCurrentState() == GameState::Options) isOptionsMenuTextVisible = true;
		if (GameStateManager::Instance().GetCurrentState() == GameState::Winner) isWinnerMenuTextVisible = true;
		
	}

	void UI::Draw(sf::RenderWindow& window)
	{
		if (isPlayingTextVisible)
		{
			playingRectangle.setPosition(SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEIGHT / 2.f);
			window.draw(playingRectangle);
			
			playingScoreText.setPosition(10.f + SETTINGS.BORDER_SIZE, 10.f + SETTINGS.BORDER_SIZE);
			playingScoreText.setOrigin(0.f, 0.f);
			window.draw(playingScoreText);
		}

		if (isMainMenuTextVisible) DrawMainMenu(window);
		if (isPauseMenuTextVisible) DrawPauseMenu(window);
		if (isNameInputMenuTextVisible) DrawNameInputMenu(window);
		if (isConfirmationMenuTextVisible) DrawConfirmationMenu(window);
		if (isGameOverMenuTextVisible) DrawGameOverMenu(window);
		if (isDifficultyMenuTextVisible) DrawDifficultyMenu(window);
		if (isScoreboardMenuVisible) DrawLeaderboard(window);
		if (isOptionsMenuTextVisible) DrawOptionsMenu(window);
		if (isWinnerMenuTextVisible) DrawWinnerMenu(window);
		
	}

	void UI::PlaySound(const sf::SoundBuffer& buffer)
	{
		if (isSoundOn)
		{
			sound.setBuffer(buffer);
			sound.setVolume(30);
			sound.play();
		}
	}

	void UI::InitPlayMusic()
	{
			musicMainTheme.setVolume(30);
			musicMainTheme.setPlayingOffset(sf::seconds(0.f));
			musicMainTheme.setLoop(true);
	}

	void UI::UpdatePlayMusic()
	{
		if (GameStateManager::Instance().GetCurrentState() == GameState::Playing) OnPlayMusic(true);
		else OnPlayMusic(false);
	}

	void UI::OnPlayMusic(bool isPlay)
	{
		if (isMusicOn)
		{
			if (isPlay) musicMainTheme.play();
			else musicMainTheme.pause();
		}
	}
}

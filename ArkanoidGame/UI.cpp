#include <string>
#include <random>
#include <cassert>
#include "UI.h"
#include "Game.h"

namespace ArkanoidGame
{
	UI::UI()
	:	isPlayingTextVisible(false),
		isMainMenuTextVisible(false),
		isPauseMenuTextVisible(false),
		isNameInputMenuTextVisible(false),
		isConfirmationMenuTextVisible(false),
		isGameOverMenuTextVisible(false),
		isDifficultyMenuTextVisible(false),
		isScoreboardMenuVisible(false),
		isOptionsMenuTextVisible(false)
	{
		
	}

	UI::~UI()
	{
	}

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
		assert(font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));
		assert(snakeTextureHead.loadFromFile(RESOURCES_PATH + "snake_head.png"));
		assert(snakeTextureBody.loadFromFile(RESOURCES_PATH + "snake_body.png"));
		assert(appleTexture.loadFromFile(RESOURCES_PATH + "apple.png"));
		assert(wallTexture.loadFromFile(RESOURCES_PATH + "wall.png"));
		assert(noneTexture.loadFromFile(RESOURCES_PATH + "none.png"));
		assert(icon.loadFromFile(RESOURCES_PATH + "icon.png"));
		assert(deathBuffer.loadFromFile(RESOURCES_PATH + "Death.wav"));
		assert(eatAppleBuffer.loadFromFile(RESOURCES_PATH + "Collision.wav"));
		assert(pressEnterBuffer.loadFromFile(RESOURCES_PATH + "Press_Enter.wav"));
		assert(selectMenuBuffer.loadFromFile(RESOURCES_PATH + "Select_Menu.wav"));
		assert(musicMainTheme.openFromFile(RESOURCES_PATH + "MainTheme.wav"));
	}

	void UI::Init()
	{
		InitResources();
		InitPauseTexture();
		noneSprite.setTexture(noneTexture);
		noneSprite.setOrigin(CELL_SIZE / 2.f, CELL_SIZE / 2.f);
		
		// Playing Resources
		InitRectangle(playingRectangle, SCREEN_WIDTH - 20.f, SCREEN_HEIGHT - 20.f,
			sf::Color::Transparent, sf::Color::White, 10.f);
		
		InitText(playingScoreText, font, 24, 0, sf::Color::White);
		
		InitText(playingInputText, font, 24, 0, sf::Color::White, "Use WASD to move, Space to restart, ESC to exit");

		// Main Menu Text
		InitMainMenu();
		
		// Pause Menu Text
		InitPauseMenu();

		// Name Input Menu Text
		InitNameInputMenu();
		
		// Confirmation Menu Text
		InitConfirmationMenu();
		
		// Leaderboard
		InitLeaderboard();
		
		// Game over Text
		InitGameOverMenu();

		// Difficulty Menu Text
		InitDifficultyMenu();

		// Options Menu Text
		InitOptionsMenu();
	}

	void UI::Update(Game& game)
	{
		playingScoreText.setString("Scores: " + std::to_string(numScores));
		gameOverScores.setString(std::to_string(numScores));
		isGameOverMenuTextVisible = game.GetCurrentGameState() == GameState::GameOver;

		if (game.GetCurrentGameState() == GameState::Playing)
		{
			isPlayingTextVisible = true;
			isMainMenuTextVisible = false;
			isPauseMenuTextVisible = false;
			isNameInputMenuTextVisible = false;
			isConfirmationMenuTextVisible = false;
			isGameOverMenuTextVisible = false;
			isDifficultyMenuTextVisible = false;
			isScoreboardMenuVisible = false;
			isOptionsMenuTextVisible = false;
		}
		
		if (game.GetCurrentGameState() == GameState::MainMenu)
		{
			isPlayingTextVisible = false;
			isMainMenuTextVisible = true;
			isPauseMenuTextVisible = false;
			isNameInputMenuTextVisible = false;
			isConfirmationMenuTextVisible = false;
			isGameOverMenuTextVisible = false;
			isDifficultyMenuTextVisible = false;
			isScoreboardMenuVisible = false;
			isOptionsMenuTextVisible = false;
		}

		if (game.GetCurrentGameState() == GameState::PauseMenu)
		{
			isPlayingTextVisible = false;
			isMainMenuTextVisible = false;
			isPauseMenuTextVisible = true;
			isNameInputMenuTextVisible = false;
			isConfirmationMenuTextVisible = false;
			isGameOverMenuTextVisible = false;
			isDifficultyMenuTextVisible = false;
			isScoreboardMenuVisible = false;
			isOptionsMenuTextVisible = false;
		}

		if (game.GetCurrentGameState() == GameState::NameInputMenu)
		{
			isPlayingTextVisible = false;
			isMainMenuTextVisible = false;
			isPauseMenuTextVisible = false;
			isNameInputMenuTextVisible = true;
			isConfirmationMenuTextVisible = false;
			isGameOverMenuTextVisible = false;
			isDifficultyMenuTextVisible = false;
			isScoreboardMenuVisible = false;
			isOptionsMenuTextVisible = false;
		}

		if (game.GetCurrentGameState() == GameState::ConfirmationMenu)
		{
			isPlayingTextVisible = false;
			isMainMenuTextVisible = false;
			isPauseMenuTextVisible = false;
			isNameInputMenuTextVisible = false;
			isConfirmationMenuTextVisible = true;
			isGameOverMenuTextVisible = false;
			isDifficultyMenuTextVisible = false;
			isScoreboardMenuVisible = false;
			isOptionsMenuTextVisible = false;
		}
		
		if (game.GetCurrentGameState() == GameState::GameOver)
		{
			isPlayingTextVisible = false;
			isMainMenuTextVisible = false;
			isPauseMenuTextVisible = false;
			isNameInputMenuTextVisible = false;
			isConfirmationMenuTextVisible = false;
			isGameOverMenuTextVisible = true;
			isDifficultyMenuTextVisible = false;
			isScoreboardMenuVisible = false;
			isOptionsMenuTextVisible = false;
		}

		if (game.GetCurrentGameState() == GameState::Difficulty)
		{
			isPlayingTextVisible = false;
			isMainMenuTextVisible = false;
			isPauseMenuTextVisible = false;
			isNameInputMenuTextVisible = false;
			isConfirmationMenuTextVisible = false;
			isGameOverMenuTextVisible = false;
			isDifficultyMenuTextVisible = true;
			isScoreboardMenuVisible = false;
			isOptionsMenuTextVisible = false;
		}
		
		if (game.GetCurrentGameState() == GameState::Leaderboard)
		{
			isPlayingTextVisible = false;
			isMainMenuTextVisible = false;
			isPauseMenuTextVisible = false;
			isNameInputMenuTextVisible = false;
			isConfirmationMenuTextVisible = false;
			isGameOverMenuTextVisible = false;
			isDifficultyMenuTextVisible = false;
			isScoreboardMenuVisible = true;
			isOptionsMenuTextVisible = false;
		}

		if (game.GetCurrentGameState() == GameState::Options)
		{
			isPlayingTextVisible = false;
			isMainMenuTextVisible = false;
			isPauseMenuTextVisible = false;
			isNameInputMenuTextVisible = false;
			isConfirmationMenuTextVisible = false;
			isGameOverMenuTextVisible = false;
			isDifficultyMenuTextVisible = false;
			isScoreboardMenuVisible = false;
			isOptionsMenuTextVisible = true;
		}

	}

	void UI::Draw(sf::RenderWindow& window)
	{
		if (isPlayingTextVisible)
		{
			playingRectangle.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
			window.draw(playingRectangle);
			
			playingScoreText.setPosition(10.f + BORDER_SIZE, 10.f + BORDER_SIZE);
			playingScoreText.setOrigin(0.f, 0.f);
			window.draw(playingScoreText);

			playingInputText.setPosition(window.getSize().x - 10.f - BORDER_SIZE, 10.f + BORDER_SIZE);
			playingInputText.setOrigin(playingInputText.getLocalBounds().width, 0.f);
			window.draw(playingInputText);
		}

		if (isMainMenuTextVisible)
		{
			DrawMainMenu(window);
		}

		if (isPauseMenuTextVisible)
		{
			OnPlayMusic(false);
			DrawPauseMenu(window);
		}

		if (isNameInputMenuTextVisible)
		{
			DrawNameInputMenu(window);
		}

		if (isConfirmationMenuTextVisible)
		{
			OnPlayMusic(false);
			DrawConfirmationMenu(window);
		}

		if (isGameOverMenuTextVisible)
		{
			OnPlayMusic(false);
			DrawGameOverMenu(window);
		}

		if (isDifficultyMenuTextVisible)
		{
			DrawDifficultyMenu(window);
		}

		if (isScoreboardMenuVisible)
		{
			DrawLeaderboard(window);
		}
		
		if (isOptionsMenuTextVisible)
		{
			DrawOptionsMenu(window);
		}
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

	void UI::OnPlayMusic(bool isPlay)
	{
		if (isMusicOn)
		{
			if (isPlay)
			{
				musicMainTheme.play();
			}
			else
			{
				musicMainTheme.pause();
			}
		}
	}
}

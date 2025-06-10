#include "UI.h"
#include "Settings.h"
#include "GameState.h"
#include "Menu/MainMenu.h"
#include "Menu/PauseMenu.h"
#include "Menu/LeaderboardMenu.h"
#include "Menu/GameOverMenu.h"

namespace ArkanoidGame {

	void UI::InitResources()
	{
		font.loadFromFile(SETTINGS.FONT_PATH);
		scoreText.setFont(font);
		scoreText.setCharacterSize(28);
		scoreText.setFillColor(sf::Color::White);
		scoreText.setPosition(20.f, 10.f);
	}

	void UI::Init()
	{
		InitResources();

		// Создаём и инициализируем все меню
		menus.emplace(GameState::MainMenu,			std::make_unique<MainMenu>());
		menus.emplace(GameState::PauseMenu,			std::make_unique<PauseMenu>());
		menus.emplace(GameState::Leaderboard,		std::make_unique<LeaderboardMenu>());
		menus.emplace(GameState::GameOver,			std::make_unique<GameOverMenu>());
		// menus.emplace(GameState::Options,			std::make_unique<OptionsMenu>());
		// menus.emplace(GameState::ConfirmationMenu,	std::make_unique<ConfirmationMenu>());
		// menus.emplace(GameState::NameInputMenu,		std::make_unique<NameInputMenu>());
		// menus.emplace(GameState::Winner,			std::make_unique<WinnerMenu>());
		

		for (auto& [state, menu] : menus)
		{
			menu->Init(font);
		}
	}

	void UI::UpdateScore(int score)
	{
		scoreText.setString("Score: " + std::to_string(score));
	}

	void UI::Draw(sf::RenderWindow& window)
	{
		GameState state = STATES.GetCurrentState();
		auto it = menus.find(state);
		if (it != menus.end())
		{
			it->second->Draw(window);
		}
		if (state == GameState::Playing) window.draw(scoreText);
	}

	void UI::HandleEvent(const sf::Event& event)
	{
		if (event.type != sf::Event::KeyPressed)
			return;

		auto state = STATES.GetCurrentState();
		auto it = menus.find(state);
		if (it == menus.end()) return;

		IMenu& menu = *it->second;

		auto key = event.key.code;

		auto IsMoveUpKey = [](sf::Keyboard::Key k)
		{
			return k == sf::Keyboard::Up || k == sf::Keyboard::W;
		};
		auto IsMoveDownKey = [](sf::Keyboard::Key k)
		{
			return k == sf::Keyboard::Down || k == sf::Keyboard::S;
		};

		if (IsMoveUpKey(key))
			menu.MoveUp();
		else if (IsMoveDownKey(key))
			menu.MoveDown();
		else if (key == sf::Keyboard::Escape)
			menu.ResetSelection();
		else if (key == sf::Keyboard::Enter)
			menu.OnConfirm();
	}

	void UI::ResetSelectionForState(GameState state)
	{
		auto it = menus.find(state);
		if (it != menus.end())
			it->second->ResetSelection();
	}

	void UI::SetScoreForState(GameState state, int score)
	{
		auto it = menus.find(state);
		if (it != menus.end())
		{
			if (auto* menu = dynamic_cast<GameOverMenu*>(it->second.get()))
			{
				menu->SetScore(score);
			}
		}
	}
}

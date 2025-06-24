#include "UI.h"
#include "Settings.h"
#include "GameState.h"
#include "Menu/MainMenu.h"
#include "Menu/PauseMenu.h"
#include "Menu/LeaderboardMenu.h"
#include "Menu/GameOverMenu.h"
#include "Menu/ConfirmationMenu.h"
#include "Menu/NameInputMenu.h"
#include "Menu/WinnerMenu.h"
#include "Scores/RecordSaveWithDefaultName.h"
#include "Scores/RecordSaveWithInputName.h"

namespace ArkanoidGame
{

	void UI::InitResources()
	{
		font.loadFromFile(SETTINGS.FONT_PATH);
		scoreText.setFont(font);
		scoreText.setCharacterSize(28);
		scoreText.setFillColor(sf::Color::White);
		scoreText.setPosition(20.f, 10.f);
		livesText.setFont(font);
		livesText.setCharacterSize(28);
		livesText.setFillColor(sf::Color::White);
		livesText.setPosition(20.f, 40.f);
	}

	void UI::Init()
	{
		InitResources();

		// Create and initialize the entire menu
		menus.emplace(GameState::MainMenu,			std::make_unique<MainMenu>());
		menus.emplace(GameState::PauseMenu,			std::make_unique<PauseMenu>());
		menus.emplace(GameState::Leaderboard,		std::make_unique<LeaderboardMenu>());
		menus.emplace(GameState::GameOver,			std::make_unique<GameOverMenu>());
		menus.emplace(GameState::ConfirmationMenu,	std::make_unique<ConfirmationMenu>());
		menus.emplace(GameState::NameInputMenu,		std::make_unique<NameInputMenu>());
		menus.emplace(GameState::Winner,			std::make_unique<WinnerMenu>());
		// menus.emplace(GameState::Options,			std::make_unique<OptionsMenu>());
		

		for (auto& [state, menu] : menus)
		{
			menu->Init(font);
		}

		if (auto* winnerMenu = dynamic_cast<WinnerMenu*>(menus.at(GameState::Winner).get()))
		{
			winnerMenu->SetOnConfirmCallback([this](int selection)
			{
				HandleWinnerMenuSelection(selection);
			});
		}
	}

	void UI::UpdateScore(int score)
	{
		scoreText.setString("Score: " + std::to_string(score));
	}

	void UI::UpdateLives(int lives)
	{
		livesText.setString("Lives: " + std::to_string(lives));
	}

	void UI::Draw(sf::RenderWindow& window)
	{
		GameState state = STATES.GetCurrentState();
		auto it = menus.find(state);
		if (it != menus.end())
		{
			it->second->Draw(window);
		}
		if (state == GameState::Playing)
		{
			window.draw(scoreText);
			window.draw(livesText);
		}
	}

	void UI::HandleEvent(const sf::Event& event)
	{
		GameState state = STATES.GetCurrentState();
	    auto it = menus.find(state);
	    if (it == menus.end()) return;

	    IMenu& menu = *it->second;

	    if (state == GameState::NameInputMenu)
	    {
	        auto* nameMenu = dynamic_cast<NameInputMenu*>(it->second.get());
	        if (nameMenu)
	        {
	        	if (event.type == sf::Event::TextEntered)
	        	{
	        	    if (event.text.unicode < 128 && std::isprint(static_cast<char>(event.text.unicode)))
	        	    {
	        	        nameMenu->AppendChar(static_cast<char>(event.text.unicode));
	        	    }
	        	}
	            if (event.type == sf::Event::KeyPressed)
	            {
	                if (event.key.code == sf::Keyboard::BackSpace)
	                {
	                    nameMenu->RemoveLastChar();
	                    return;
	                }
	                if (event.key.code == sf::Keyboard::Enter)
	                {
	                    ExecuteRecordSaveStrategy();
	                    return;
	                }
	            }
	        }
	    }

	    if (event.type != sf::Event::KeyPressed) return;

	    auto key = event.key.code;
	    auto IsMoveUpKey = [](sf::Keyboard::Key k) {
	        return k == sf::Keyboard::Up || k == sf::Keyboard::W;
	    };
	    auto IsMoveDownKey = [](sf::Keyboard::Key k) {
	        return k == sf::Keyboard::Down || k == sf::Keyboard::S;
	    };

	    if (IsMoveUpKey(key)) menu.MoveUp();
	    else if (IsMoveDownKey(key)) menu.MoveDown();
	    else if (key == sf::Keyboard::Escape) menu.ResetSelection();
	    else if (key == sf::Keyboard::Enter) menu.OnConfirm();

	    if (state == GameState::ConfirmationMenu && key == sf::Keyboard::Enter)
	    {
	        auto* confMenu = dynamic_cast<ConfirmationMenu*>(it->second.get());
	        if (confMenu)
	        {
	            if (confMenu->GetSelection() == ConfirmationMenu::Choice::Yes)
	            {
	                recordSaveStrategy = std::make_unique<RecordSaveWithInputName>(*this);
	                STATES.PushState(GameState::NameInputMenu);
	            }
	            else
	            {
	                recordSaveStrategy = std::make_unique<RecordSaveWithDefaultName>();
	                ExecuteRecordSaveStrategy();
	            }
	        }
	    }
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
			else if (auto* winnerMenu = dynamic_cast<WinnerMenu*>(it->second.get()))
			{
				winnerMenu->SetScore(score);
			}
		}
	}

	void UI::HandleGameOver(int score)
	{
		pendingScore = score;
		if (recordManager.IsNewRecord(score))
		{
			STATES.PushState(GameState::ConfirmationMenu);
		}
		else
		{
			STATES.PushState(GameState::GameOver);
			SetScoreForState(GameState::GameOver, score);
		}
	}

	void UI::HandleWinnerMenuSelection(int selection) const
	{
		if (selection == 0)
		{
			STATES.SwitchState(GameState::Playing);
			if (nextLevelCallback) nextLevelCallback();
		}
		else if (selection == 1)
		{
			STATES.SwitchState(GameState::MainMenu);
		}
	}

	IMenu* UI::GetMenu(GameState state)
	{
		auto it = menus.find(state);
		if (it != menus.end()) return it->second.get();
		return nullptr;
	}

	void UI::ExecuteRecordSaveStrategy()
	{
		if (recordSaveStrategy)
		{
		    recordSaveStrategy->Save(recordManager, pendingScore);
		
		    auto* gameOverMenu = dynamic_cast<GameOverMenu*>(GetMenu(GameState::GameOver));
		    if (gameOverMenu)
		    {
		        LeaderboardMenu temp;
		        temp.LoadRecordsFromFile(SETTINGS.LEADERBOARD_FILENAME);
		        gameOverMenu->UpdateRecords(temp.GetRecords(), font);
		    }
		
		    auto* leaderboardMenu = dynamic_cast<LeaderboardMenu*>(GetMenu(GameState::Leaderboard));
		    if (leaderboardMenu)
		    {
		        leaderboardMenu->UpdateRecords(font);
		    }
		
		    STATES.SwitchState(GameState::GameOver);
		    SetScoreForState(GameState::GameOver, pendingScore);
		    recordSaveStrategy.reset();
		}
	}
}

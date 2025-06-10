#include "GameOverMenu.h"

#include "../GameState.h"
#include "../Game.h"

namespace ArkanoidGame
{
    void GameOverMenu::Init(const sf::Font& font)
    {
        static const std::vector<std::string> labels = { "NEW GAME", "MAIN MENU" };
        InitCommon(font, "Game Over", labels, 72.f, 50.f);
      
        // Текст для счета
        scoreTitle.setFont(font);
        scoreTitle.setString("Number of points");
        scoreTitle.setCharacterSize(48);
        scoreTitle.setFillColor(sf::Color::White);
        scoreTitle.setOrigin(scoreTitle.getLocalBounds().width/2.f, scoreTitle.getLocalBounds().height);
        
        scoreValue.setFont(font);
        scoreValue.setCharacterSize(48);
        scoreValue.setFillColor(sf::Color::White);
        scoreValue.setOrigin(0.f, 0.f);
        
        // Заголовок таблицы рекордов
        recordsTitle.setFont(font);
        recordsTitle.setString("Records:");
        recordsTitle.setCharacterSize(40);
        recordsTitle.setFillColor(sf::Color::White);
        recordsTitle.setOrigin(recordsTitle.getLocalBounds().width/2.f, recordsTitle.getLocalBounds().height);
    }
      
    void GameOverMenu::SetScore(int score)
    {
        scoreValue.setString(std::to_string(score));
        scoreValue.setOrigin(scoreValue.getLocalBounds().width/2.f, scoreValue.getLocalBounds().height/2.f);
    }
      
    void GameOverMenu::Draw(sf::RenderWindow& window)
    {
        // Рисуем фон
        background.setPosition(SETTINGS.SCREEN_WIDTH/2.f, SETTINGS.SCREEN_HEIGHT/2.f);
        window.draw(background);
      
        // Рисуем заголовок меню и счет
        scoreTitle.setPosition(SETTINGS.SCREEN_WIDTH/2.f, scoreTitle.getLocalBounds().height);
        window.draw(scoreTitle);
      
        scoreValue.setPosition(SETTINGS.SCREEN_WIDTH/2.f, scoreTitle.getPosition().y + scoreTitle.getLocalBounds().height);
        window.draw(scoreValue);
      
        // Рисуем рекорды
        recordsTitle.setPosition(SETTINGS.SCREEN_WIDTH/2.f, scoreValue.getPosition().y + scoreValue.getLocalBounds().height + 100.f);
        window.draw(recordsTitle);
      
        // TODO: отрисовка leaderboardItems через DrawItems()
      
        // Рисуем пункты меню
        DrawItems(window, items, SETTINGS.SCREEN_WIDTH/2.f, SETTINGS.SCREEN_HEIGHT - 100.f * items.size(), 60.f);
    }

    void GameOverMenu::OnConfirm()
    {
        switch (GetSelectedIndex())
        {
        case 0:
            {
                Game::ResetGameStartedFlag();
                STATES.SwitchState(GameState::Playing);
                break;
            }
        default:    STATES.PushState(GameState::MainMenu);    break;
        }
    }
}

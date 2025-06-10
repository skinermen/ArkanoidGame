#include "MainMenu.h"
#include <cassert>
#include "../GameState.h"

namespace ArkanoidGame
{
    void MainMenu::Init(const sf::Font& font)
    {
        static const std::vector<std::string> labels =
        {
            "START GAME", "LEADERBOARD", "OPTIONS", "EXIT"
        };
        InitCommon(font, "Arkanoid Game", labels, 72.f, 50.f);
    }

    void MainMenu::Draw(sf::RenderWindow& window)
    {
        background.setPosition(SETTINGS.SCREEN_WIDTH/2.f, SETTINGS.SCREEN_HEIGHT/2.f);
        window.draw(background);

        title.setPosition(SETTINGS.SCREEN_WIDTH/2.f, title.getLocalBounds().height);
        window.draw(title);

        DrawItems(window, items, SETTINGS.SCREEN_WIDTH/2.f, SETTINGS.SCREEN_HEIGHT/4.f, 60.f);
    }

    void MainMenu::OnConfirm()
    {
        switch (GetSelectedIndex())
        {
        case 0:     STATES.PushState(GameState::Playing);     break;
        case 1:     STATES.PushState(GameState::Leaderboard); break;
        case 2:     STATES.PushState(GameState::Options);     break;
        default:    STATES.PushState(GameState::Exit);        break;
        }
    }
}
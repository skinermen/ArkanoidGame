#include "PauseMenu.h"
#include "../GameState.h"

namespace ArkanoidGame
{
    void PauseMenu::Init(const sf::Font& font)
    {
        static const std::vector<std::string> labels = { "RESUME", "MAIN MENU" };
        InitCommon(font, "Paused", labels, 60.f, 40.f);
    }

    void PauseMenu::Draw(sf::RenderWindow& window)
    {
        background.setPosition(SETTINGS.SCREEN_WIDTH/2.f,
                               SETTINGS.SCREEN_HEIGHT/2.f);
        window.draw(background);
        
        title.setPosition(SETTINGS.SCREEN_WIDTH/2.f,
                          title.getLocalBounds().height);
        window.draw(title);
        
        DrawItems(window, items, SETTINGS.SCREEN_WIDTH/2.f, SETTINGS.SCREEN_HEIGHT/4.f, 50.f);
    }

    void PauseMenu::OnConfirm()
    {
        switch (GetSelectedIndex())
        {
        case 0:     STATES.PopState();                            break;
        default:    STATES.PushState(GameState::MainMenu);        break;
        }
    }
}

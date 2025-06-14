#include "ConfirmationMenu.h"

namespace ArkanoidGame
{
    void ConfirmationMenu::Init(const sf::Font& font)
    {
        static const std::vector<std::string> labels = { "Yes", "No" };
        InitCommon(font, "Enter the name?", labels, 60.f, 40.f);
    }
  
    void ConfirmationMenu::Draw(sf::RenderWindow& window)
    {
        background.setPosition(SETTINGS.SCREEN_WIDTH/2.f, SETTINGS.SCREEN_HEIGHT/2.f);
        window.draw(background);
  
        title.setPosition(SETTINGS.SCREEN_WIDTH/2.f, title.getLocalBounds().height);
        window.draw(title);
  
        DrawItems(window, items, SETTINGS.SCREEN_WIDTH/2.f, SETTINGS.SCREEN_HEIGHT/4.f, 60.f);
    }

    void ConfirmationMenu::OnConfirm(){}

    ConfirmationMenu::Choice ConfirmationMenu::GetSelection() const
    {
        return static_cast<Choice>(selectedIndex);
    }
}
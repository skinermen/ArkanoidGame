#include "NameInputMenu.h"

namespace ArkanoidGame
{
    void NameInputMenu::Init(const sf::Font& font)
    {
        InitCommon(font, "Enter your name:", {}, 48.f, 0.f);

        nameText.setFont(font);
        nameText.setCharacterSize(40);
        nameText.setFillColor(sf::Color::White);
        // nameText.setFillColor(sf::Color::Red);
        nameText.setString("");
    }

    void NameInputMenu::Draw(sf::RenderWindow& window)
    {
        background.setPosition(SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEIGHT / 2.f);
        window.draw(background);

        title.setPosition(SETTINGS.SCREEN_WIDTH / 2.f, title.getLocalBounds().height);
        window.draw(title);

        // Обновляем текст с именем перед отрисовкой
        nameText.setString(playerName);
        nameText.setOrigin(nameText.getLocalBounds().width / 2.f, nameText.getLocalBounds().height / 2.f);
        nameText.setPosition(SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEIGHT / 2.f);
        // nameText.setOrigin(0.f, 0.f);
        // nameText.setPosition(50.f, 50.f);
        window.draw(nameText);
    }

    void NameInputMenu::OnConfirm(){}

    void NameInputMenu::AppendChar(char c)
    {
        playerName.push_back(c);
        nameText.setString(playerName);
    }

    void NameInputMenu::RemoveLastChar()
    {
        if (!playerName.empty())
        {
            playerName.pop_back();
            nameText.setString(playerName); // сразу обновляем текст
        }
    }

    void NameInputMenu::Reset()
    {
        playerName.clear();
    }

    const std::string& NameInputMenu::GetPlayerName() const
    {
        return playerName;
    }
}

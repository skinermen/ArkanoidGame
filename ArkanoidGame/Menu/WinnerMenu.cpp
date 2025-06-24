#include "WinnerMenu.h"

namespace ArkanoidGame
{
    void WinnerMenu::Init(const sf::Font& font)
    {
        // General initialization: heading and menu items
        static const std::vector<std::string> labels = { "NEXT LEVEL", "MAIN MENU" };
        InitCommon(font, "The level is passed", labels, 72.f, 50.f);
        
        // Preparation of text to display an account
        scoreTitle.setFont(font);
        scoreTitle.setString("Number of points: ");
        scoreTitle.setCharacterSize(48);
        scoreTitle.setFillColor(sf::Color::White);
        scoreTitle.setOrigin
        (
            scoreTitle.getLocalBounds().width / 2.f,
            scoreTitle.getLocalBounds().height
        );

        scoreValue.setFont(font);
        scoreValue.setCharacterSize(48);
        scoreValue.setFillColor(sf::Color::White);

        combinedTextScores.setFont(font);
        combinedTextScores.setCharacterSize(48);
        combinedTextScores.setFillColor(sf::Color::Yellow);
        combinedTextScores.setOrigin(0.f, 0.f);
    }

    void WinnerMenu::SetScore(int score)
    {
        scoreValue.setString(std::to_string(score));
        scoreValue.setOrigin
        (
            scoreValue.getLocalBounds().width / 2.f,
            scoreValue.getLocalBounds().height / 2.f
        );
    }

    void WinnerMenu::Draw(sf::RenderWindow& window)
    {
        // We draw the background
        background.setPosition
        (
            SETTINGS.SCREEN_WIDTH / 2.f,
            SETTINGS.SCREEN_HEIGHT / 2.f
        );
        window.draw(background);

        // We draw a title
        title.setPosition
        (
            SETTINGS.SCREEN_WIDTH / 2.f,
            title.getLocalBounds().height
        );
        window.draw(title);
        
        // Combined headline of the number of points scored
        combinedTextScores.setString(scoreTitle.getString() + scoreValue.getString());
        sf::FloatRect bounds = combinedTextScores.getLocalBounds();
        combinedTextScores.setPosition ( SETTINGS.SCREEN_WIDTH / 2.f - (bounds.width / 2.f + bounds.left), 100.f );
        window.draw(combinedTextScores);
        
        // We draw menu items at the bottom of the screen
        DrawItems(window, items, SETTINGS.SCREEN_WIDTH / 2.f,
            SETTINGS.SCREEN_HEIGHT - 100.f * items.size(), 60.f
        );
    }

    void WinnerMenu::OnConfirm()
    {
        if (onConfirmCallback)
        {
            onConfirmCallback(GetSelectedIndex());
        }
    }

    void WinnerMenu::SetOnConfirmCallback(std::function<void(int)> cb)
    {
        onConfirmCallback = std::move(cb);
    }
}

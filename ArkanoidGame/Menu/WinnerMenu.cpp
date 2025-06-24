#include "WinnerMenu.h"
#include "../GameState.h"

namespace ArkanoidGame
{
    void WinnerMenu::Init(const sf::Font& font)
    {
        // Общая инициализация: заголовок и пункты меню
        static const std::vector<std::string> labels = { "NEXT LEVEL", "MAIN MENU" };
        InitCommon(font, "You Win!", labels, 72.f, 50.f);

        // Подготовка текста для отображения счета
        scoreTitle.setFont(font);
        scoreTitle.setString("Your score:");
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
        // Рисуем фон
        background.setPosition
        (
            SETTINGS.SCREEN_WIDTH / 2.f,
            SETTINGS.SCREEN_HEIGHT / 2.f
        );
        window.draw(background);

        // Рисуем заголовок
        title.setPosition
        (
            SETTINGS.SCREEN_WIDTH / 2.f,
            title.getLocalBounds().height
        );
        window.draw(title);

        // Рисуем текст "Your score:" и значение
        float yOffset = title.getPosition().y + title.getLocalBounds().height + 20.f;
        scoreTitle.setPosition
        (
            SETTINGS.SCREEN_WIDTH / 2.f,
            yOffset
        );
        window.draw(scoreTitle);

        scoreValue.setPosition
        (
            SETTINGS.SCREEN_WIDTH / 2.f,
            yOffset + scoreTitle.getLocalBounds().height + 10.f
        );
        window.draw(scoreValue);

        // Рисуем пункты меню внизу экрана
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

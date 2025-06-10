#include "MenuBase.h"

namespace ArkanoidGame
{

    void MenuBase::InitCommon(const sf::Font& font,
                              const std::string& titleStr,
                              const std::vector<std::string>& itemStrs,
                              float titleSize,
                              float itemSize)
    {
        // фон
        background.setSize({SETTINGS.SCREEN_WIDTH-20, SETTINGS.SCREEN_HEIGHT-20});
        background.setOrigin(background.getSize()/2.f);
        background.setFillColor(sf::Color::Black);
        background.setOutlineColor(sf::Color::White);
        background.setOutlineThickness(10.f);

        // заголовок
        title.setFont(font);
        title.setString(titleStr);
        title.setCharacterSize(static_cast<int>(titleSize));
        title.setFillColor(sf::Color::Magenta);
        title.setOrigin(title.getLocalBounds().width/2.f, title.getLocalBounds().height);

        // пункты меню
        items.clear();
        for (size_t i = 0; i < itemStrs.size(); ++i) {
            sf::Text t;
            t.setFont(font);
            t.setString(itemStrs[i]);
            t.setCharacterSize(static_cast<int>(itemSize));
            t.setFillColor(i==0 ? sf::Color::Green : sf::Color::White);
            items.push_back(t);
        }
    }

    void MenuBase::DrawItems(sf::RenderWindow& window,
                             const std::vector<sf::Text>& items,
                             float posX, float posY, float indent)
    {
        float y = posY;
        for (auto& t : items)
        {
            sf::Text copy = t;
            copy.setOrigin(copy.getLocalBounds().width/2.f, 0);
            copy.setPosition(posX, y);
            window.draw(copy);
            y += indent;
        }
    }

    void MenuBase::MoveUp()
    {
        if (selectedIndex == 0) return;
        items[selectedIndex].setFillColor(sf::Color::White);
        --selectedIndex;
        items[selectedIndex].setFillColor(sf::Color::Green);
    }

    void MenuBase::MoveDown()
    {
        if (selectedIndex+1 >= items.size()) return;
        items[selectedIndex].setFillColor(sf::Color::White);
        ++selectedIndex;
        items[selectedIndex].setFillColor(sf::Color::Green);
    }

    void MenuBase::ResetSelection()
    {
        for (auto& t : items) t.setFillColor(sf::Color::White);
        selectedIndex = 0;
        items[0].setFillColor(sf::Color::Green);
    }

}
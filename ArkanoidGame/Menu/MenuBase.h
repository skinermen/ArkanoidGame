#pragma once
#include "IMenu.h"
#include "../Settings.h"

#include <vector>
#include <string>

namespace ArkanoidGame
{

    class MenuBase : public IMenu
    {
    protected:
        sf::RectangleShape background;
        sf::Text title;
        std::vector<sf::Text> items;
        unsigned int selectedIndex = 0;

        void InitCommon(const sf::Font& font,
                        const std::string& titleStr,
                        const std::vector<std::string>& itemStrs,
                        float titleSize,
                        float itemSize);
        static void DrawItems(sf::RenderWindow& window,
                              const std::vector<sf::Text>& items,
                              float posX, float posY, float indent);

    public:
        void MoveUp() override;
        void MoveDown() override;
        void ResetSelection() override;
        unsigned int GetSelectedIndex() const override { return selectedIndex; }
    };
}

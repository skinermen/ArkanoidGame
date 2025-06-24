#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Bonus.h"

namespace ArkanoidGame
{
    class BonusManager
    {
    public:
        void Update(sf::RenderWindow& window, float dt, class Platform& platform, Ball& ball);
        void Draw(sf::RenderWindow& window) const;
        void SpawnBonus(std::unique_ptr<Bonus> bonus);
        void Clear();
    private:
        std::vector<std::unique_ptr<Bonus>> bonuses;
    };
}
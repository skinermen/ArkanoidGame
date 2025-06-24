#pragma once
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <vector>
#include "Bricks/Brick.h"

namespace ArkanoidGame
{
    struct GameMemento
    {
        std::vector<std::shared_ptr<Brick>> bricks;
        sf::Vector2f ballPosition;
        sf::Vector2f ballVelocity;
        sf::Vector2f platformPosition;
        int score = 0;
        int currentLevel = 0;
    };
}
#pragma once

#include "Brick.h"
#include <vector>
#include <memory>

namespace ArkanoidGame
{
    class BrickManager
    {
    public:
        BrickManager();
        ~BrickManager();

        void Init();
        void Update(sf::RenderWindow& window, float deltaTime) const;
        void Draw(sf::RenderWindow& window) const;
        bool AllBricksDestroyed() const;
        void SetBall(Ball* b) { ball = b; }

    private:
        std::vector<std::unique_ptr<Brick>> bricks;
        Ball* ball;
    };
}

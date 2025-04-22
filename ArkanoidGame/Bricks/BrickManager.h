#pragma once

#include "Brick.h"
#include <vector>
#include <memory>

namespace ArkanoidGame
{
    class BrickManager  // NOLINT(cppcoreguidelines-special-member-functions)
    {
    public:
        BrickManager();
        ~BrickManager();

        void Init();
        void Update() const;
        void Draw(sf::RenderWindow& window) const;
        bool AllBricksDestroyed() const;

        const std::vector<std::unique_ptr<Brick>>& GetBricks() const {return bricks;}

    private:
        std::vector<std::unique_ptr<Brick>> bricks;
    };
}

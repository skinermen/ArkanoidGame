#include "BrickManager.h"
#include "Constants.h"
#include "GameState.h"

namespace ArkanoidGame
{
    BrickManager::BrickManager() = default;

    BrickManager::~BrickManager() = default;

    void BrickManager::Init()
    {
        bricks.clear();
        
        float totalWidth = BRICK_COLUMNS * BRICK_WIDTH + (BRICK_COLUMNS - 1) * BRICK_SPACING;
        float startX = (SCREEN_WIDTH - totalWidth) / 2.f + BRICK_WIDTH / 2.f;
        float startY = 50.f;

        for (int row = 0; row < BRICK_ROW; ++row)
        {
            for (int col = 0; col < BRICK_COLUMNS; ++col)
            {
                float x = startX + col * (BRICK_WIDTH + BRICK_SPACING);
                float y = startY + row * (BRICK_HEIGHT + BRICK_SPACING);

                auto brick = std::make_unique<Brick>(sf::Vector2f(x, y), sf::Vector2f(BRICK_WIDTH, BRICK_HEIGHT), sf::Color::Green);
                bricks.push_back(std::move(brick));
            }
        }
    }

    void BrickManager::Update(sf::RenderWindow& window, float deltaTime) const
    {
        bool allBricksDestroyed = true;
        for (const auto& brick : bricks)
        {
            if (!brick->IsDestroyed())
            {
                allBricksDestroyed = false;
                break;
            }
        }

        if (allBricksDestroyed)
        {
            GameStateManager::Instance().SwitchState(GameState::Winner);
        }
    }

    void BrickManager::Draw(sf::RenderWindow& window) const
    {
        for (const auto& brick : bricks)
        {
            brick->Draw(window);
        }
    }

    bool BrickManager::AllBricksDestroyed() const
    {
        for (const auto& brick : bricks)  // NOLINT(readability-use-anyofallof)
        {
            if (!brick->IsDestroyed())
                return false;
        }
        return true;
    }
}

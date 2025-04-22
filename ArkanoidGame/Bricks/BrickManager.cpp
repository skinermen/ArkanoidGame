#include "BrickManager.h"
#include "../Constants.h"
#include "../GameState.h"
#include "SimpleBrick.h"
#include "StrongBrick.h"
#include "IndestructibleBrick.h"
#include "GlassBrick.h"

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
                sf::Vector2f position(x, y);
                sf::Vector2f size(BRICK_WIDTH, BRICK_HEIGHT);
                
                
                // Тип блока зависит от строки
                std::unique_ptr<Brick> brick;

                if (row == 0)
                {
                    brick = std::make_unique<IndestructibleBrick>(position, size);
                }
                else if (row == 1)
                {
                    brick = std::make_unique<GlassBrick>(position, size);
                }
                else if (row % 2 == 0)
                {
                    brick = std::make_unique<StrongBrick>(position, size);
                }
                else
                {
                    brick = std::make_unique<SimpleBrick>(position, size);
                }

                bricks.push_back(std::move(brick));
            }
        }
    }

    void BrickManager::Update() const
    {
        if (AllBricksDestroyed())
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
            if (!brick->IsDestroyed() && dynamic_cast<IndestructibleBrick*>(brick.get()) == nullptr)
            {
                return false;
            }
        }
        return true;
    }
}

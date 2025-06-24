#include <cassert>

#include "BrickManager.h"
#include "../Settings.h"
#include "../GameState.h"
#include "SimpleBrick.h"
#include "StrongBrick.h"
#include "UnbreackableBrick.h"
#include "GlassBrick.h"

namespace ArkanoidGame
{
    BrickManager::BrickManager()
    {
        // Инициализируем все фабрики
        factories[BlockType::Simple]        = std::make_unique<SimpleBrickFactory>();
        factories[BlockType::Strong]        = std::make_unique<StrongBrickFactory>();
        factories[BlockType::Glass]         = std::make_unique<GlassBrickFactory>();
        factories[BlockType::Unbreackable] = std::make_unique<UnbreackableBrickFactory>();

        // Если нужно, сбросим счётчики:
        for (auto& [type, factory] : factories)
            factory->ClearCounter();
    }

    BrickManager::~BrickManager() = default;

    sf::Vector2f BrickManager::CellToPixel(const sf::Vector2i& cellCoords) const
    {
        float totalWidth = SETTINGS.BRICK_COLUMNS * SETTINGS.BRICK_WIDTH
                         + (SETTINGS.BRICK_COLUMNS - 1) * SETTINGS.BRICK_SPACING;
        float startX = (SETTINGS.SCREEN_WIDTH - totalWidth) / 2.f + SETTINGS.BRICK_WIDTH / 2.f;
        float startY = 50.f;

        int cellX = cellCoords.x;
        int cellY = cellCoords.y;

        float px = startX + cellX * (SETTINGS.BRICK_WIDTH + SETTINGS.BRICK_SPACING);
        float py = startY + cellY * (SETTINGS.BRICK_HEIGHT + SETTINGS.BRICK_SPACING);
        return { px, py };
    }

    void BrickManager::Init(int levelIndex)
    {
        bricks.clear();

        // Проверяем, что хотя бы один уровень загрузился:
        int totalLevels = levelLoader.GetLevelCount();
        assert(totalLevels > 0 && "No levels were loaded! Check LEVELS_CONFIG_PATH.");

        // Если levelIndex выходит за диапазон, например передали 5, а есть только 1 уровень:
        assert(levelIndex >= 0 && levelIndex < totalLevels);

        Level& lvl = levelLoader.GetLevel(levelIndex);
        for (auto& [cellCoords, type] : lvl.mBlocks)
        {
            CreateBrickAt(cellCoords, type);
        }
    }

    void BrickManager::CreateBrickAt(const sf::Vector2i& cellCoords, BlockType type)
    {
        // Конвертируем «ячейку → пиксели»
        sf::Vector2f position = CellToPixel(cellCoords);
        // Размер кирпича
        sf::Vector2f size(SETTINGS.BRICK_WIDTH, SETTINGS.BRICK_HEIGHT);

        auto it = factories.find(type);
        if (it == factories.end())
        {
            assert(false && "Unknown BlockType in BrickManager::CreateBrickAt");
            return;
        }
        // Вызываем фабрику
        std::shared_ptr<Brick> newBrick = it->second->CreateBrick(position, size);
        bricks.push_back(std::move(newBrick));
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
        for (const auto& brick : bricks)
        {
            if (!brick->IsDestroyed() && dynamic_cast<UnbreackableBrick*>(brick.get()) == nullptr)
            {
                return false;
            }
        }
        return true;
    }

    int BrickManager::GetTotalLevels()
    {
        return levelLoader.GetLevelCount();
    }
}

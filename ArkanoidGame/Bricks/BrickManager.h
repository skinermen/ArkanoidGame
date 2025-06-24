#pragma once

#include <vector>
#include <memory>

#include "Brick.h"
#include "LevelLoader.h"
#include "BrickFactory.h"

namespace ArkanoidGame
{
    class BrickManager
    {
    public:
        BrickManager();
        ~BrickManager();

        // Теперь Init принимает индекс уровня
        void Init(int levelIndex);
        void Update() const;
        void Draw(sf::RenderWindow& window) const;
        bool AllBricksDestroyed() const;
        int GetTotalLevels();
        
        const std::vector<std::shared_ptr<Brick>>& GetBricks() const { return bricks; }
        int GetScore() const { return score; }
        void AddScore(int value) { score += value; }
        void ResetScore() { score = 0; }

    private:
        // Перевод «координаты ячейки (int, int) → координаты пикселей (float, float)»
        sf::Vector2f CellToPixel(const sf::Vector2i& cellCoords) const;

        // Основной вектор кирпичей
        std::vector<std::shared_ptr<Brick>> bricks;

        // Словарь «BlockType → своя фабрика»
        std::map<BlockType, std::unique_ptr<BrickFactory>> factories;

        // Загрузчик уровней, который в конструкторе уже прочитает файл уровней
        LevelLoader levelLoader;

        // Вспомогательный метод: создаёт и кладёт Кирпич нужного типа
        void CreateBrickAt(const sf::Vector2i& cellCoords, BlockType type);

        int score = 0;
    };
}

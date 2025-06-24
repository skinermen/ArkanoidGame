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
        
        void Init(int levelIndex);
        void Update() const;
        void Draw(sf::RenderWindow& window) const;
        bool AllBricksDestroyed() const;
        int GetTotalLevels();
        
        const std::vector<std::shared_ptr<Brick>>& GetBricks() const { return bricks; }
        int GetScore() const { return score; }
        void AddScore(int value) { score += value; }
        void ResetScore() { score = 0; }
        void SetScore(int value) { score = value; }
        void SetBricks(std::vector<std::shared_ptr<Brick>> newBricks) { bricks = std::move(newBricks); }

    private:
        // Translation "Coordinates of the cell (int, int) → Pixel coordinates (Float, Float)"
        sf::Vector2f CellToPixel(const sf::Vector2i& cellCoords) const;

        // The main vector of bricks
        std::vector<std::shared_ptr<Brick>> bricks;

        // Dictionary "Blocktype → Your Factory"
        std::map<BlockType, std::unique_ptr<BrickFactory>> factories;

        // Level bootloader, which in the constructor will already read the level file
        LevelLoader levelLoader;

        // Auxiliary method: creates and warehouses Brick the necessary type
        void CreateBrickAt(const sf::Vector2i& cellCoords, BlockType type);

        int score = 0;
    };
}

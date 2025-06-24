#pragma once
#include <vector>
#include <map>

#include "SFML/System/Vector2.hpp"

namespace ArkanoidGame
{
    enum class BlockType
    {
        Simple,
        Strong,
        Unbreackable,
        Glass
    };
    
    struct Level
    {
        // Now it is Vector2i - (column, line) in the grid
        std::vector<std::pair<sf::Vector2i, BlockType>> mBlocks;
    };
    
    class LevelLoader final
    {
    public:
        LevelLoader() { LoadLevelsFromFile(); }
        Level& GetLevel(int i);
        ~LevelLoader();
        int GetLevelCount() const;
    private:
        void LoadLevelsFromFile();

        static BlockType CharToBlockType(char symbol);
        std::vector<Level> levels;
    };
}

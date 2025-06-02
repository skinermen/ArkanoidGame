#pragma once
#include <vector>
#include <string>
#include <memory>
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
        // Теперь именно Vector2i — (колонка, строка) в сетке
        std::vector<std::pair<sf::Vector2i, BlockType>> mBlocks;
    };
    
    class LevelLoader final
    {
    public:
        LevelLoader() { LoadLevelsFromFile(); }
        Level& GetLevel(int i);
        ~LevelLoader() = default;
        int GetLevelCount();
    private:
        void LoadLevelsFromFile();

        static BlockType CharToBlockType(char symbol);
        std::vector<Level> levels;
    };
}

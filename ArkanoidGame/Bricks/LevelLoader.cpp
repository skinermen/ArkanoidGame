#include "LevelLoader.h"
#include "../Settings.h"

#include <fstream>
#include <cassert>
#include <filesystem>



namespace ArkanoidGame
{
    Level& LevelLoader::GetLevel(int i)
    {
        return levels.at(i);
    }

    LevelLoader::~LevelLoader(){}

    BlockType LevelLoader::CharToBlockType(char symbol)
    {
        BlockType blockType;
        switch (symbol)
        {
        case '1':
            blockType = BlockType::Simple;
            break;
        case '2':
            blockType = BlockType::Strong;
            break;
        case '0':
            blockType = BlockType::Unbreackable;
            break;
        case '4':
            blockType = BlockType::Glass;
            break;
        default:
            assert(false);
            break;
        }
        return blockType;
    }

    void LevelLoader::LoadLevelsFromFile()
    {
        std::string filepath = SETTINGS.LEVELS_CONFIG_PATH;
        std::string line;
        std::ifstream file(filepath);
        int y = 0;
        while (getline(file, line))
        {
            if (line.rfind("level ", 0) == 0)
            {
                auto level = std::stoi(line.substr(6, line.size() - 6));
                levels.emplace_back(Level());
                y = 0;
            }
            else
            {
                int x = 0;
                for (char c : line)
                {
                    if (c != ' ')
                    {
                        levels.back().mBlocks.emplace_back(std::make_pair(sf::Vector2i{ x, y }, CharToBlockType(c)));
                    }
                    ++x;
                }
            }
            ++y;
        }
        file.close();
    }

    int LevelLoader::GetLevelCount() const
    {
        return levels.size();
    }




}

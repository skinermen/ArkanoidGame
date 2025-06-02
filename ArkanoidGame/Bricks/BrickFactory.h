#pragma once
#include <memory>
#include "SFML//Graphics.hpp"


namespace ArkanoidGame
{
    class Brick;
    
    class BrickFactory
    {
    public:
        virtual ~BrickFactory() = default;
        virtual std::shared_ptr<Brick> CreateBrick(const sf::Vector2f& position, const sf::Vector2f& size) = 0;
        int GetCreatedBreackableBricksCount();
        void ClearCounter();
        
        protected:
        int createdBreackableBricksCount = 0;
    };

    class SimpleBrickFactory final : public BrickFactory
    {
    public:
        std::shared_ptr<Brick> CreateBrick(const sf::Vector2f& position,
                                           const sf::Vector2f& size) override;
        ~SimpleBrickFactory() override = default;
    };
    
    class StrongBrickFactory final : public BrickFactory
    {
    public:
        std::shared_ptr<Brick> CreateBrick(const sf::Vector2f& position,
                                           const sf::Vector2f& size) override;
        ~StrongBrickFactory() override = default;
    };
    
    class GlassBrickFactory final : public BrickFactory
    {
    public:
        std::shared_ptr<Brick> CreateBrick(const sf::Vector2f& position,
                                           const sf::Vector2f& size) override;
        ~GlassBrickFactory() override = default;
    };
    
    class UnbreackableBrickFactory final : public BrickFactory
    {
    public:
        std::shared_ptr<Brick> CreateBrick(const sf::Vector2f& position,
                                           const sf::Vector2f& size) override;
        ~UnbreackableBrickFactory() override = default;
    };
}

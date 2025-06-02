#include "BrickFactory.h"
#include "SimpleBrick.h"
#include "StrongBrick.h"
#include "GlassBrick.h"
#include "UnbreackableBrick.h"

namespace ArkanoidGame
{
    // ---------------- SimpleBrickFactory ----------------
    std::shared_ptr<Brick> SimpleBrickFactory::CreateBrick(const sf::Vector2f& position,
                                                           const sf::Vector2f& size)
    {
        ++createdBreackableBricksCount;
        return std::make_shared<SimpleBrick>(position, size);
    }

    // ---------------- StrongBrickFactory ----------------
    std::shared_ptr<Brick> StrongBrickFactory::CreateBrick(const sf::Vector2f& position,
                                                           const sf::Vector2f& size)
    {
        ++createdBreackableBricksCount;
        return std::make_shared<StrongBrick>(position, size);
    }

    // ---------------- GlassBrickFactory ----------------
    std::shared_ptr<Brick> GlassBrickFactory::CreateBrick(const sf::Vector2f& position,
                                                          const sf::Vector2f& size)
    {
        ++createdBreackableBricksCount;
        return std::make_shared<GlassBrick>(position, size);
    }

    // ---------------- UnbreackableBrickFactory ----------------
    std::shared_ptr<Brick> UnbreackableBrickFactory::CreateBrick(const sf::Vector2f& position,
                                                                 const sf::Vector2f& size)
    {
        return std::make_shared<UnbreackableBrick>(position, size);
    }

    void BrickFactory::ClearCounter()
    {
        createdBreackableBricksCount = 0;
    }

    int BrickFactory::GetCreatedBreackableBricksCount()
    {
        return createdBreackableBricksCount;
    }
}

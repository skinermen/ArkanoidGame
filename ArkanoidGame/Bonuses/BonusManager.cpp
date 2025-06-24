#include "BonusManager.h"
#include "../Platform.h"
#include "../Ball.h"

namespace ArkanoidGame
{
    void BonusManager::Update(sf::RenderWindow& window, float dt, Platform& platform, Ball& ball)
    {
        for (auto it = bonuses.begin(); it != bonuses.end(); )
        {
            auto& bonus = *it;
            bonus->Update(window, dt);
            if (bonus->GetBounds().intersects(platform.GetShape().getGlobalBounds()))
            {
                bonus->Apply(ball, platform);
            }
            if (bonus->IsCollected() || bonus->IsOffScreen())
            {
                it = bonuses.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    void BonusManager::Draw(sf::RenderWindow& window) const
    {
        for (const auto& bonus : bonuses)
            bonus->Draw(window);
    }

    void BonusManager::SpawnBonus(std::unique_ptr<Bonus> bonus)
    {
        bonuses.push_back(std::move(bonus));
    }

    void BonusManager::Clear()
    {
        bonuses.clear();
    }
}
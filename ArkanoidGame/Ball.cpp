#include "Ball.h"
#include "Bricks/Brick.h"
#include "Platform.h"
#include "BallStrategies.h"

#include <memory>
#include <algorithm>
#include <cmath>

namespace ArkanoidGame
{
    Ball::Ball()
    {
        ballShape.setRadius(SETTINGS.SIZE_BALL);
        ballShape.setFillColor(sf::Color::White);
        ballShape.setOrigin(ballShape.getRadius(), ballShape.getRadius());
        ballShape.setPosition(SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEIGHT / 2.f);
        strategy = std::make_unique<NormalBallStrategy>();
    }

    void Ball::Update(sf::RenderWindow& window, float deltaTime)
    {
        ballShape.move(velocity * deltaTime);
        if (strategy)
            strategy->Update(*this, deltaTime);

        sf::Vector2f pos = ballShape.getPosition();
        float radius = ballShape.getRadius();

        // We check the collision with the left and right edges
        if (pos.x - radius < 0.f)
        {
            pos.x = radius;
            velocity.x = -velocity.x;
        }
        else if (pos.x + radius > SETTINGS.SCREEN_WIDTH)
        {
            pos.x = SETTINGS.SCREEN_WIDTH - radius;
            velocity.x = -velocity.x;
        }

        // We check the collision with the upper border
        if (pos.y - radius < 0.f)
        {
            pos.y = radius;
            velocity.y = -velocity.y;
        }

        ballShape.setPosition(pos);
        if (strategy && strategy->IsFinished())
        {
            SetStrategy(std::make_unique<NormalBallStrategy>());
        }
    }

    void Ball::Draw(sf::RenderWindow& window) const
    {
        window.draw(ballShape);
    }

    void Ball::Reset()
    {
        // Throw the ball into the center of the screen and set the initial direction
        ballShape.setPosition(SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEIGHT / 2.f);
        velocity = SETTINGS.INITIAL_DIRECTION_OF_THE_BALL;
        SetStrategy(std::make_unique<NormalBallStrategy>());
    }

    void Ball::SetPosition(const sf::Vector2f& pos)
    {
        ballShape.setPosition(pos);
    }

    sf::Vector2f Ball::GetPosition() const
    {
        return ballShape.getPosition();
    }

    bool Ball::CheckCollisionWithPlatform(const Platform& platform) const
    {
        sf::Vector2f ballPos = ballShape.getPosition();
        float radius = ballShape.getRadius();
        sf::FloatRect platformBounds = platform.GetShape().getGlobalBounds();

        // Find the nearest point on the rectangle to the center of the ball
        float closestX = std::max(platformBounds.left, std::min(ballPos.x, platformBounds.left + platformBounds.width));
        float closestY = std::max(platformBounds.top, std::min(ballPos.y, platformBounds.top + platformBounds.height));

        float distanceX = ballPos.x - closestX;
        float distanceY = ballPos.y - closestY;
        float distanceSquared = distanceX * distanceX + distanceY * distanceY;

        return distanceSquared < (radius * radius);
    }

    bool Ball::CheckCollisionWithBrick(const Brick& brick) const
    {
        sf::Vector2f ballPos = ballShape.getPosition();
        float radius = ballShape.getRadius();
        sf::FloatRect brickBounds = brick.GetBounds();
        
        // Find the nearest point on the rectangle of brick to the center of the ball
        float closestX = std::max(brickBounds.left, std::min(ballPos.x, brickBounds.left + brickBounds.width));
        float closestY = std::max(brickBounds.top, std::min(ballPos.y, brickBounds.top + brickBounds.height));
        
        float distanceX = ballPos.x - closestX;
        float distanceY = ballPos.y - closestY;
        float distanceSquared = distanceX * distanceX + distanceY * distanceY;
        
        return distanceSquared < (radius * radius);
    }

    int Ball::CollisionHandlingWithObjects(const Platform& platform, const std::vector<std::shared_ptr<Brick>>& bricks)
    {
        int pointsEarned = 0;
        
        // Check Collision With Platform
        if (CheckCollisionWithPlatform(platform))
        {
            // We get the boundaries of the platform and its center
            sf::FloatRect platformBounds = platform.GetShape().getGlobalBounds();
            float platformCenterX = platformBounds.left + platformBounds.width / 2.f;
    
            // We calculate the displacement of the blow from the center of the platform (in the range [-1, 1])
            sf::Vector2f ballPos = GetShape().getPosition();
            float offset = (ballPos.x - platformCenterX) / (platformBounds.width / 2.f);
    
            // The new direction of direction: the horizontal component depends on Offset, the vertical is fixed (rebound up)
            sf::Vector2f newDir(offset, -1.f);
            float len = std::sqrt(newDir.x * newDir.x + newDir.y * newDir.y);
            newDir.x /= len;
            newDir.y /= len;
    
            // We retain the current ball speed
            float currentSpeed = std::sqrt(
                GetVelocity().x * GetVelocity().x +
                GetVelocity().y * GetVelocity().y
            );
    
            // We update the speed of the ball with a new direction
            SetVelocity(newDir * currentSpeed);
    
            // Additionally, you can move the ball just above the platform to avoid stuck
            SetPosition(sf::Vector2f(ballPos.x, platformBounds.top - GetShape().getRadius()));
        }

        // Check Collision With Bricks
        for (auto& brick : bricks)
        {
            if (!brick->IsDestroyed() && CheckCollisionWithBrick(*brick))
            {
                bool shouldBounce = strategy ? strategy->OnBrickHit(*this, *brick) : brick->OnHit();

                if (brick->IsDestroyed())
                    pointsEarned += brick->GetScore();
                
                sf::FloatRect brickBounds = brick->GetBounds();
                sf::Vector2f brickCenter(brickBounds.left + brickBounds.width / 2.f,
                                         brickBounds.top + brickBounds.height / 2.f);
        
                sf::Vector2f ballPos = GetPosition();
                float radius = GetShape().getRadius();
        
                float dx = ballPos.x - brickCenter.x;
                float dy = ballPos.y - brickCenter.y;
        
                float combinedHalfWidth = (brickBounds.width / 2.f) + radius;
                float combinedHalfHeight = (brickBounds.height / 2.f) + radius;
        
                float overlapX = combinedHalfWidth - std::abs(dx);
                float overlapY = combinedHalfHeight - std::abs(dy);
                
                if (shouldBounce)  // If the ball must bounce
                {
                    if (overlapX < overlapY)
                    {
                        SetVelocity(sf::Vector2f(-GetVelocity().x, GetVelocity().y));
        
                        if (dx > 0)
                            SetPosition(sf::Vector2f(brickBounds.left + brickBounds.width + radius, ballPos.y));
                        else
                            SetPosition(sf::Vector2f(brickBounds.left - radius, ballPos.y));
                    }
                    else
                    {
                        SetVelocity(sf::Vector2f(GetVelocity().x, -GetVelocity().y));
        
                        if (dy > 0)
                            SetPosition(sf::Vector2f(ballPos.x, brickBounds.top + brickBounds.height + radius));
                        else
                            SetPosition(sf::Vector2f(ballPos.x, brickBounds.top - radius));
                    }
                }
            }
        }
        return pointsEarned;
    }

    void Ball::SetStrategy(std::unique_ptr<BallStrategy> newStrategy)
    {
        if (strategy)
            strategy->OnExit(*this);
        strategy = std::move(newStrategy);
        if (!strategy)
            strategy = std::make_unique<NormalBallStrategy>();
        strategy->OnEnter(*this);
    }
}

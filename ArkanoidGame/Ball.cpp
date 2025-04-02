#include "Ball.h"
#include "Brick.h"
#include "Platform.h"

#include <algorithm>

namespace ArkanoidGame
{
    Ball::Ball()
    {
        ballShape.setRadius(SIZE_BALL);
        ballShape.setFillColor(sf::Color::White);
        ballShape.setOrigin(ballShape.getRadius(), ballShape.getRadius());
        ballShape.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
    }

    void Ball::Update(sf::RenderWindow& window, float deltaTime)
    {
        ballShape.move(velocity * deltaTime);

        sf::Vector2f pos = ballShape.getPosition();
        float radius = ballShape.getRadius();

        // We check the collision with the left and right edges
        if (pos.x - radius < 0.f)
        {
            pos.x = radius;
            velocity.x = -velocity.x;
        }
        else if (pos.x + radius > SCREEN_WIDTH)
        {
            pos.x = SCREEN_WIDTH - radius;
            velocity.x = -velocity.x;
        }

        // We check the collision with the upper border
        if (pos.y - radius < 0.f)
        {
            pos.y = radius;
            velocity.y = -velocity.y;
        }

        ballShape.setPosition(pos);
    }

    void Ball::Draw(sf::RenderWindow& window) const
    {
        window.draw(ballShape);
    }

    void Ball::Reset()
    {
        // Throw the ball into the center of the screen and set the initial direction
        ballShape.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
        velocity = INITIAL_DIRECTION_OF_THE_BALL;
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
        // Получаем границы кирпича
        sf::FloatRect brickBounds = brick.GetBounds();
        
        // Находим ближайшую точку на прямоугольнике кирпича к центру шарика
        float closestX = std::max(brickBounds.left, std::min(ballPos.x, brickBounds.left + brickBounds.width));
        float closestY = std::max(brickBounds.top, std::min(ballPos.y, brickBounds.top + brickBounds.height));
        
        float distanceX = ballPos.x - closestX;
        float distanceY = ballPos.y - closestY;
        float distanceSquared = distanceX * distanceX + distanceY * distanceY;
        
        return distanceSquared < (radius * radius);
    }
}

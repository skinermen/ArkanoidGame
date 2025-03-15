#include "Platform.h"

namespace ArkanoidGame
{
    Platform::Platform()
    {
        // The size of the platform
        platformShape.setSize(sf::Vector2f(SIZE_PLATFORM_X, SIZE_PLATFORM_Y));
        platformShape.setFillColor(sf::Color::White);
        platformShape.setOrigin(platformShape.getSize() / 2.f);
        // The initial position
        platformShape.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 50.f);

        // Initialize lastMousePosition
        lastMousePosition = platformShape.getPosition();
    }

    void Platform::Update(const sf::RenderWindow& window, float deltaTime)
    {
        // The current position of the mouse relative to the window
        sf::Vector2i mousePosInt = sf::Mouse::getPosition(window);
        sf::Vector2f currentMousePos(static_cast<float>(mousePosInt.x), static_cast<float>(mousePosInt.y));

        // If the mouse has shifted more than Mousemove Threshold, switch to mouse control
        if (std::abs(currentMousePos.x - lastMousePosition.x) > mouseMoveThreshold)
        {
            useMouseControl = true;
        }

        // If the keys are pressed left or right, we switch to keyboard control
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            useMouseControl = false;
        }

        // We maintain the current mouse position for the next iteration
        lastMousePosition = currentMousePos;

        // Control depending on the selected method
        if (useMouseControl)
        {
            // Mouse management
            platformShape.setPosition(currentMousePos.x, platformShape.getPosition().y);
        }
        else
        {
            // Keyboard management
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                platformShape.move(-speed * deltaTime, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                platformShape.move(speed * deltaTime, 0);
            }
        }

        // Limiting the movement of the platform within the screen
        sf::Vector2f pos = platformShape.getPosition();
        float halfWidth = platformShape.getSize().x / 2.f;
        if (pos.x - halfWidth < 0)
            pos.x = halfWidth;
        if (pos.x + halfWidth > SCREEN_WIDTH)
            pos.x = SCREEN_WIDTH - halfWidth;
        platformShape.setPosition(pos);
    }

    void Platform::Draw(sf::RenderWindow& window) const
    {
        window.draw(platformShape);
    }

    void Platform::SetPosition(float x, float y)
    {
        platformShape.setPosition(x, y);
    }
}

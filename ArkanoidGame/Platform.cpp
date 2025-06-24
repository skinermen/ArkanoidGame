#include "Platform.h"

namespace ArkanoidGame
{
    Platform::Platform()
    {
        // The size of the platform
        platformShape.setSize(sf::Vector2f(SETTINGS.SIZE_PLATFORM_X, SETTINGS.SIZE_PLATFORM_Y));
        platformShape.setFillColor(sf::Color::White);
        platformShape.setOrigin(platformShape.getSize() / 2.f);
        // The initial position
        platformShape.setPosition(SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEIGHT - 50.f);

        defaultSize = platformShape.getSize();
        
        // Initialize lastMousePosition
        lastMousePosition = platformShape.getPosition();
    }

    void Platform::Update(sf::RenderWindow& window, float deltaTime)
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
        if (pos.x + halfWidth > SETTINGS.SCREEN_WIDTH)
            pos.x = SETTINGS.SCREEN_WIDTH - halfWidth;
        platformShape.setPosition(pos);

        if (sizeModified)
        {
            bonusTimer -= deltaTime;
            if (bonusTimer <= 0.f)
            {
                SetSize(defaultSize);
                sizeModified = false;
            }
        }
    }

    void Platform::Draw(sf::RenderWindow& window) const
    {
        window.draw(platformShape);
    }

    void Platform::SetPosition(const sf::Vector2f& pos)
    {
        platformShape.setPosition(pos);
    }

    void Platform::SetSize(const sf::Vector2f& size)
    {
        sf::Vector2f pos = platformShape.getPosition();
        platformShape.setSize(size);
        platformShape.setOrigin(size / 2.f);
        platformShape.setPosition(pos);
    }

    void Platform::ApplySizeBonus(float factor, float duration)
    {
        SetSize(sf::Vector2f(defaultSize.x * factor, defaultSize.y));
        bonusTimer = duration;
        sizeModified = true;
    }

    void Platform::ResetSize()
    {
        SetSize(defaultSize);
        sizeModified = false;
        bonusTimer = 0.f;
    }

    sf::Vector2f Platform::GetPosition() const
    {
        return platformShape.getPosition();
    }
}

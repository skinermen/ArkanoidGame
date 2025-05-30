﻿#include "GlassBrick.h"

namespace ArkanoidGame
{
    GlassBrick::GlassBrick(const sf::Vector2f& position, const sf::Vector2f& size)
        : Brick(position, size, sf::Color::Transparent, sf::Color::White, 2.f) {}

    bool GlassBrick::OnHit()
    {
        destroyed = true;
        return false;
    }
}

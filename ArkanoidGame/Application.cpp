﻿#include "Application.h"

namespace ArkanoidGame
{
    Application& Application::Instance()
    {
        static Application instance;
        return instance;
    }
    
    Application::Application() :
        window(sf::VideoMode(ArkanoidGame::SCREEN_WIDTH, ArkanoidGame::SCREEN_HEIGHT), GAME_NAME), game(window)
    {
        // Init random number generator
        int seed = static_cast<int>(time(nullptr));
        srand(seed);
    }

    Application::~Application() = default;

    void Application::Run()
    {
        // Init game clocks
        // ReSharper disable once CppTooWideScope
        sf::Clock gameClock;

        // Main loop
        while (window.isOpen())
        {
            // Reduce framerate to not spam CPU and GPU
            sleep(sf::milliseconds(16));

            // Read events for close window
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                    break;
                }
            }

            // Calculate time delta
            float currentTime = gameClock.getElapsedTime().asSeconds();

            //Update game state
            game.Update(currentTime, window, event);

            // Draw game
            window.clear();
            game.Draw(window);

            window.display();
        }
    }



}
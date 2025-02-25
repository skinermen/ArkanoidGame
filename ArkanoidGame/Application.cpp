#include "Application.h"

namespace SnakeGame
{
    Application::Application(const std::string& gameName) :
        window(sf::VideoMode(SnakeGame::SCREEN_WIDTH, SnakeGame::SCREEN_HEIGHT), "SnakeGame")
    {
        // Init random number generator
        int seed = static_cast<int>(time(nullptr));
        srand(seed);

        InitGame(game,window);
    }

    Application::~Application()
    {
        ShutdownGame(game);
    }

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
            UpdateGame(game, currentTime, window, event);

            // Draw game
            window.clear();
            DrawGame(game, window);

            window.display();
        }
    }



}
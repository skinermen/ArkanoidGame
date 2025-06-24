#include "GameOverMenu.h"

#include "../GameState.h"
#include "../Game.h"

namespace ArkanoidGame
{
    void GameOverMenu::Init(const sf::Font& font)
    {
        static const std::vector<std::string> labels = { "NEW GAME", "MAIN MENU" };
        InitCommon(font, "Game Over", labels, 72.f, 50.f);
      
        // Scores text
        scoreTitle.setFont(font);
        scoreTitle.setString("Number of points: ");
        scoreTitle.setCharacterSize(48);
        scoreTitle.setOrigin(scoreTitle.getLocalBounds().width/2.f, scoreTitle.getLocalBounds().height);
        
        scoreValue.setFont(font);
        scoreValue.setCharacterSize(48);
        scoreValue.setOrigin(0.f, 0.f);

        combinedTextScores.setFont(font);
        combinedTextScores.setCharacterSize(48);
        combinedTextScores.setFillColor(sf::Color::Yellow);
        combinedTextScores.setOrigin(0.f, 0.f);
        
        // Title of the record table
        recordsTitle.setFont(font);
        recordsTitle.setString("Records:");
        recordsTitle.setCharacterSize(40);
        recordsTitle.setFillColor(sf::Color::Magenta);
        recordsTitle.setOrigin(recordsTitle.getLocalBounds().width/2.f, recordsTitle.getLocalBounds().height);

        // Record table
        LeaderboardMenu tempMenu;
        tempMenu.LoadRecordsFromFile(SETTINGS.LEADERBOARD_FILENAME);
        records = tempMenu.GetRecords();
        leaderboardItems.clear();
        for (size_t i = 0; i < SETTINGS.SIZE_MINI_LEADERBOARD; ++i)
        {
            sf::Text t;
            t.setFont(font);
            t.setCharacterSize(32);
            t.setFillColor(sf::Color::White);
            t.setString(std::to_string(i + 1) + ". " + records[i].playerName + " - " + std::to_string(records[i].score));
            leaderboardItems.push_back(t);
        }
    }
      
    void GameOverMenu::SetScore(int score)
    {
        scoreValue.setString(std::to_string(score));
        scoreValue.setOrigin(scoreValue.getLocalBounds().width / 2.f, scoreValue.getLocalBounds().height / 2.f);
    }
      
    void GameOverMenu::Draw(sf::RenderWindow& window)
    {
        // Background
        background.setPosition(SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEIGHT / 2.f);
        window.draw(background);

        // Combined headline of the number of points scored
        combinedTextScores.setString(scoreTitle.getString() + scoreValue.getString());
        sf::FloatRect bounds = combinedTextScores.getLocalBounds();
        combinedTextScores.setPosition ( SETTINGS.SCREEN_WIDTH / 2.f - (bounds.width / 2.f + bounds.left), 0.f );
        window.draw(combinedTextScores);

        // Fitting of Records
        recordsTitle.setPosition(SETTINGS.SCREEN_WIDTH / 2.f, combinedTextScores.getPosition().y + bounds.height + 100.f);
        window.draw(recordsTitle);

        // Leaderboard (The first SIZE_MINI_LEADERBOARD leaders)
        DrawItems(window, leaderboardItems, SETTINGS.SCREEN_WIDTH / 2.f, recordsTitle.getPosition().y + 20.f, 40.f);
        
        // Menu items
        DrawItems(window, items, SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEIGHT - 100.f * items.size(), 60.f);
    }

    void GameOverMenu::OnConfirm()
    {
        switch (GetSelectedIndex())
        {
        case 0:
            {
                Game::ResetGameStartedFlag();
                STATES.SwitchState(GameState::Playing);
                break;
            }
        default:    STATES.PushState(GameState::MainMenu);    break;
        }
    }

    void GameOverMenu::UpdateRecords(const std::vector<SLeaderboard>& newRecords, const sf::Font& font)
    {
        records = newRecords;
        leaderboardItems.clear();
        for (size_t i = 0; i < SETTINGS.SIZE_MINI_LEADERBOARD && i < records.size(); ++i)
        {
            sf::Text t;
            t.setFont(font);
            t.setCharacterSize(32);
            t.setFillColor(sf::Color::White);
            t.setString(std::to_string(i + 1) + ". " + records[i].playerName + " - " + std::to_string(records[i].score));
            leaderboardItems.push_back(t);
        }
    }
}

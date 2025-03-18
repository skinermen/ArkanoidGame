#pragma once
#include <stack>

namespace ArkanoidGame
{
    enum class GameState
    {
        None,
        MainMenu,
        Playing,
        PauseMenu,
        NameInputMenu,
        ConfirmationMenu,
        GameOver,
        Leaderboard,
        Difficulty,
        Options
    };

    class GameStateManager
    {
    public:
        static GameStateManager& Instance();
        
        void PushState(GameState state);
        void SwitchState(GameState state);
        GameState GetCurrentState() const;
        GameState GetPreviousState() const;
        void ClearStates();

    private:
        GameStateManager() = default;
        ~GameStateManager() = default;
        GameStateManager(const GameStateManager&) = delete;
        GameStateManager& operator=(const GameStateManager&) = delete;

        std::stack<GameState> stateStack;
    };
}

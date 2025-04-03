#include "GameState.h"

namespace ArkanoidGame
{
    GameStateManager& GameStateManager::Instance()
    {
        static GameStateManager instance;
        return instance;
    }

    void GameStateManager::PushState(GameState state)
    {
        stateStack.push(state);
    }

    void GameStateManager::SwitchState(GameState state)
    {
        if (!stateStack.empty())
            stateStack.pop();
        stateStack.push(state);
    }

    GameState GameStateManager::GetCurrentState() const
    {
        if (!stateStack.empty())
            return stateStack.top();
        return GameState::None;
    }

    GameState GameStateManager::GetPreviousState() const
    {
        if (stateStack.size() < 2)
            return GameState::None;
        
        std::stack<GameState> tempStack = stateStack;
        tempStack.pop();
        return tempStack.top();
    }

    void GameStateManager::ClearStates()
    {
        while (!stateStack.empty())
            stateStack.pop();
    }

    void GameStateManager::PopState()
    {
        if (!stateStack.empty())
            stateStack.pop();
    }
}

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

#include "GameState.h"
#include "Menu/IMenu.h"
#include "Scores/RecordManager.h"
#include "Scores/IRecordSaveStrategy.h"


namespace ArkanoidGame
{	
	class UI
	{
	public:
		UI() = default;
		virtual ~UI() = default;

		void Init();
		void UpdateScore(int score);
		void Draw(sf::RenderWindow& window);
		void HandleEvent(const sf::Event& event);
		void ResetSelectionForState(GameState state);
		void SetScoreForState(GameState state, int score);

		void HandleGameOver(int score);

		IMenu* GetMenu(GameState state);
		void ExecuteRecordSaveStrategy();
	
	private:
		void InitResources();

		std::unique_ptr<IRecordSaveStrategy> recordSaveStrategy;
		int pendingScore = 0;
		RecordManager recordManager;
		sf::Text scoreText;
		sf::Font font;
		std::map<GameState, std::unique_ptr<IMenu>> menus;
	};
}

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "GameState.h"
#include "Menu/IMenu.h"


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
	
	private:
		void InitResources();

		sf::Text scoreText;
		sf::Font font;
		std::map<GameState, std::unique_ptr<IMenu>> menus;
	};
}

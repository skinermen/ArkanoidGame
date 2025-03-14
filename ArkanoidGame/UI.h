#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace ArkanoidGame
{
	class Game; // Forward declaration
	
	class UI
	{
	public:
		UI();
		~UI();

		virtual  void InitPauseTexture() = 0;
		virtual  void InitMainMenu() = 0;
		virtual  void InitPauseMenu() = 0;
		virtual  void InitNameInputMenu() = 0;
		virtual  void InitConfirmationMenu() = 0;
		virtual  void InitLeaderboard() = 0;
		virtual  void InitGameOverMenu() = 0;
		virtual  void InitDifficultyMenu() = 0;
		virtual  void InitOptionsMenu() = 0;
		virtual  void DrawMainMenu(sf::RenderWindow& window) = 0;
		virtual  void DrawPauseMenu(sf::RenderWindow& window) = 0;
		virtual  void DrawNameInputMenu(sf::RenderWindow& window) = 0;
		virtual  void DrawConfirmationMenu(sf::RenderWindow& window) = 0;
		virtual  void DrawGameOverMenu(sf::RenderWindow& window) = 0;
		virtual  void DrawDifficultyMenu(sf::RenderWindow& window) = 0;
		virtual  void DrawLeaderboard(sf::RenderWindow& window) = 0;
		virtual  void DrawOptionsMenu(sf::RenderWindow& window) = 0;

		void Init();
		void InitText(sf::Text& text, const sf::Font& font, int size, int style, sf::Color color, const std::string& name = "none");
		void InitRectangle(sf::RectangleShape& rectangle, float sizeX, float sizeY, sf::Color fillColor, sf::Color outlineColor, float outlineThickness);
		void InitResources();
		void Update(Game& game);
		void Draw(sf::RenderWindow& window);
		void PlaySound(const sf::SoundBuffer& buffer);
		void InitPlayMusic();
		void OnPlayMusic(bool isPlay);

		sf::SoundBuffer GetSelectMenuBuffer() { return selectMenuBuffer; }
		sf::SoundBuffer GetPressEnterBuffer() { return pressEnterBuffer; }
		sf::Sprite GetNoneSprite() { return noneSprite; }
		sf::Texture GetWallTexture() { return wallTexture; }
		sf::Texture GetSnakeTextureHead() { return snakeTextureHead; }
		sf::Texture GetSnakeTextureBody() { return snakeTextureBody; }
		sf::Texture GetAppleTexture() { return appleTexture; }
		sf::SoundBuffer GetDeathBuffer() { return deathBuffer; }
		sf::SoundBuffer GetEatAppleBuffer() { return eatAppleBuffer; }
		int& GetNumScores() { return numScores; }
		void SetNumScores(int newValue) { numScores = newValue; }
		bool GetIsSoundOn() { return isSoundOn; }
		bool SwitchIsSoundOn() { return !isSoundOn; }
		bool GetIsMusicOn() { return isMusicOn; }
		bool SwitchIsMusicOn() { return !isMusicOn; }

	private:
		bool isPlayingTextVisible;
		bool isMainMenuTextVisible;
		bool isPauseMenuTextVisible;
		bool isNameInputMenuTextVisible;
		bool isConfirmationMenuTextVisible;
		bool isGameOverMenuTextVisible;
		bool isDifficultyMenuTextVisible;
		bool isScoreboardMenuVisible;
		bool isOptionsMenuTextVisible;
		bool isSoundOn = true;
		bool isMusicOn = true;

		int numScores = 0;
		
		sf::RectangleShape playingRectangle;
		sf::Text playingScoreText;
		sf::Text playingInputText;

		// Resources
		sf::Sprite noneSprite;
		sf::Texture snakeTextureHead;
		sf::Texture snakeTextureBody;
		sf::Texture appleTexture;
		sf::Texture wallTexture;
		sf::Texture noneTexture;
		sf::Sound sound;
		sf::SoundBuffer eatAppleBuffer;
		sf::SoundBuffer deathBuffer;
		sf::SoundBuffer pressEnterBuffer;
		sf::SoundBuffer selectMenuBuffer;
		sf::Music musicMainTheme;
		sf::Image icon;

	protected:
		sf::Font font;
		sf::Text gameOverScores;
	};
}
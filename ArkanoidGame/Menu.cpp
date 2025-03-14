#include <string>
#include "Menu.h"
#include <fstream>
#include <iostream>
#include "Game.h"

namespace ArkanoidGame
{
	Menu::Menu()
	{
		
	}

	Menu::~Menu()
	{
	}

	void Menu::InitPauseTexture()
	{
		pauseBlurTexture.create(SCREEN_WIDTH, SCREEN_HEIGHT);
		pauseBlurTexture.clear(sf::Color(0, 0, 0, 220));
		pauseBlurSprite.setTexture(pauseBlurTexture.getTexture());
	}
	
	void Menu::InitMainMenu()
	{
		InitRectangle(mainMenuRectangleBackground, SCREEN_WIDTH - 20.f, SCREEN_HEIGHT - 20.f,
			sf::Color::Black, sf::Color::White, 10.f);
		
		InitText(mainMenuTitle, font, 72, 1, sf::Color::White,
			"SNAKE");
		
		for (int i = 0; i < VStringMainMenuItems.size(); i++)  // NOLINT(clang-diagnostic-sign-compare)
		{
			sf::Text menuItem;
			InitText(menuItem, font, 50, 1, (i == 0 ? sf::Color::Green : sf::Color::White),
				VStringMainMenuItems[i]);
			vTextMainMenuItems.push_back(menuItem);
		}
	}
	
	void Menu::InitPauseMenu()
	{
		InitRectangle(pauseMenuRectangleBackground, SCREEN_WIDTH - 20.f, SCREEN_HEIGHT - 20.f,
			sf::Color::Transparent, sf::Color::White, 10.f);
		InitText(pauseMenuTitle, font, 64, 1, sf::Color::White, "Pause menu");
		
		for (int i = 0; i < VStringPauseMenuItems.size(); i++)  // NOLINT(clang-diagnostic-sign-compare)
		{
			sf::Text menuItem;
			InitText(menuItem, font, 50, 1, (i == 0 ? sf::Color::Green : sf::Color::White),
				VStringPauseMenuItems[i]);
			vTextPauseMenuItems.push_back(menuItem);
		}
	}

	void Menu::InitNameInputMenu()
	{
		InitRectangle(nameInputMenuRectangleBackground, SCREEN_WIDTH - 20.f, SCREEN_HEIGHT - 20.f,
			sf::Color::Black, sf::Color::White, 10.f);
		InitText(nameInputMenuText, font, 40, 1, sf::Color::White,
			"Enter your name: ");
	}

	void Menu::InitConfirmationMenu()
	{
		InitRectangle(confirmationMenuRectangleBackground, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 3.7f,
			sf::Color::Transparent, sf::Color::White, 10.f);
		InitText(confirmationMenuText, font, 50, 1, sf::Color::White,
			"Enter the name");

		for (int i = 0; i < VStringConfirmationMenuItems.size(); i++)  // NOLINT(clang-diagnostic-sign-compare)
		{
			sf::Text menuItem;
			InitText(menuItem, font, 40, 1, (i == 0 ? sf::Color::Green : sf::Color::White),
				VStringConfirmationMenuItems[i]);
			vTextConfirmationMenuItems.push_back(menuItem);
		}
	}

	void Menu::InitGameOverMenu()
	{
		InitRectangle(gameOverRectangleBackground, SCREEN_WIDTH - BORDER_SIZE * 2,
			SCREEN_HEIGHT - BORDER_SIZE * 2, sf::Color::Black, sf::Color::White, 10.f);
		InitText(gameOverScoreTitle, font, 48, 1, sf::Color::White,
			"Number of points");
		InitText(gameOverScores, font, 48, 1, sf::Color::White);
		InitText(gameOverRecordsTitle, font, 40, 1, sf::Color::White,
			"Records:");
		
		for (int i = 0; i < VStringGameOverMenuItems.size(); i++)  // NOLINT(clang-diagnostic-sign-compare)
		{
			sf::Text menuItem;
			InitText(menuItem, font, 50, 1, (i == 0 ? sf::Color::Green : sf::Color::White),
				VStringGameOverMenuItems[i]);
			vTextGameOverMenuItems.push_back(menuItem);
		}
		InitGameOverLeaderboardItems();
	}

	void Menu::InitGameOverLeaderboardItems()
	{
		vTextGameOverLeaderboardItems.clear();
		for (int i = 0; i < SIZE_MINI_LEADERBOARD; i++)  // NOLINT(clang-diagnostic-sign-compare)
		{
			sf::Text recordText;
			InitText(recordText, font, 30, 1, sf::Color::White, std::to_string(i + 1)
				+ ". " + std::to_string(VLeaderboardItems[i].score));
			vTextGameOverLeaderboardItems.push_back(recordText);
		}
	}

	void Menu::InitDifficultyMenu()
	{
		InitRectangle(difficultyMenuRectangleBackground, SCREEN_WIDTH - BORDER_SIZE * 2,
			SCREEN_HEIGHT - BORDER_SIZE * 2, sf::Color::Black, sf::Color::White, 10.f);
		InitText(difficultyMenuTitle, font, 48, 1, sf::Color::White,
			"Choosing the difficulty");

		for (int i = 0; i < VStringDifficultyMenuItems.size(); i++)  // NOLINT(clang-diagnostic-sign-compare)
		{
			sf::Text menuItem;
			InitText(menuItem, font, 50, 1, (i == 0 ? sf::Color::Green : sf::Color::White),
				VStringDifficultyMenuItems[i].nameDifficulty);
			vTextDifficultyMenuItems.push_back(menuItem);
		}
	}
	
	void Menu::InitLeaderboard()
	{
		InitRectangle(leaderboardRectangleBackground, SCREEN_WIDTH - BORDER_SIZE * 2,
			SCREEN_HEIGHT - BORDER_SIZE * 2, sf::Color::Black, sf::Color::White, 10.f);
		
		InitText(leaderboardTextTitle, font, 48, 1, sf::Color::White,
			"Scoreboard:");
		InitText(leaderboardTextInstructions, font, 24, 1, sf::Color::White,
			"Press B to return to the main menu");
		
		VLeaderboardItems.clear();
		LoadRecordsFromFile(VLeaderboardItems, LEADERBOARD_FILENAME);
		vTextLeaderboardItems.clear();
		for (int i = 0; i < VLeaderboardItems.size(); ++i)  // NOLINT(clang-diagnostic-sign-compare)
		{
			sf::Text recordText;
			InitText(recordText, font, 38, 1, sf::Color::White, std::to_string(i + 1)
				+ ". " + VLeaderboardItems[i].playerName + " - "
				+ std::to_string(VLeaderboardItems[i].score));
			vTextLeaderboardItems.push_back(recordText);
		}
	}

	void Menu::InitOptionsMenu()
	{
		InitRectangle(optionsMenuRectangleBackground, SCREEN_WIDTH - BORDER_SIZE * 2,
			SCREEN_HEIGHT - BORDER_SIZE * 2, sf::Color::Black, sf::Color::White, 10.f);
		
		InitText(optionsMenuTitle, font, 60, 1, sf::Color::White,
			"Options");
		for (int i = 0; i < VStringOptionsMenuItems.size(); i++)  // NOLINT(clang-diagnostic-sign-compare)
		{
			sf::Text menuItem;
			InitText(menuItem, font, 40, 1, (i == 0 ? sf::Color::Green : sf::Color::White),
				VStringOptionsMenuItems[i]);
			vTextOptionsMenuItems.push_back(menuItem);
			
			sf::RectangleShape rectangleItem;
			InitRectangle(rectangleItem, vTextOptionsMenuItems[0].getLocalBounds().height,
				vTextOptionsMenuItems[0].getLocalBounds().height,
				sf::Color::White, sf::Color::White, 5.f);
			vRectanglesOptionsMenu.push_back(rectangleItem);
		}
	}

	void Menu::DrawMainMenu(sf::RenderWindow& window)
	{		
		mainMenuRectangleBackground.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
		window.draw(mainMenuRectangleBackground);
		
		mainMenuTitle.setPosition(SCREEN_WIDTH / 2.f, mainMenuTitle.getLocalBounds().height);
		window.draw(mainMenuTitle);
		
		DrawMenuItems(window, vTextMainMenuItems,
			SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 4.f, 60.f);
	}
	
	void Menu::DrawPauseMenu(sf::RenderWindow& window)
	{
		window.draw(pauseBlurSprite);
		
		pauseMenuRectangleBackground.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
		window.draw(pauseMenuRectangleBackground);
			
		pauseMenuTitle.setPosition(SCREEN_WIDTH / 2.f, pauseMenuTitle.getLocalBounds().height);
		pauseMenuTitle.setOrigin(pauseMenuTitle.getLocalBounds().width / 2.f,
			pauseMenuTitle.getLocalBounds().height);
		window.draw(pauseMenuTitle);

		DrawMenuItems(window, vTextPauseMenuItems,
			SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 4.f, 60.f);
	}

	void Menu::DrawNameInputMenu(sf::RenderWindow& window)
	{
		nameInputMenuRectangleBackground.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
		window.draw(nameInputMenuRectangleBackground);

		nameInputMenuText.setOrigin(nameInputMenuText.getLocalBounds().width / 2.f,
			nameInputMenuText.getLocalBounds().height / 2.f);
		nameInputMenuText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.5f);
		window.draw(nameInputMenuText);
	}

	void Menu::DrawConfirmationMenu(sf::RenderWindow& window)
	{
		mainMenuRectangleBackground.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
		window.draw(mainMenuRectangleBackground);
		
		window.draw(pauseBlurSprite);

		confirmationMenuRectangleBackground.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
		window.draw(confirmationMenuRectangleBackground);
		
		confirmationMenuText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.5f);
		window.draw(confirmationMenuText);

		DrawMenuItems(window, vTextConfirmationMenuItems,
			SCREEN_WIDTH / 2.f, confirmationMenuText.getLocalBounds().width, 40.f);
	}
	
	void Menu::DrawGameOverMenu(sf::RenderWindow& window)
	{
		InitGameOverLeaderboardItems();
		
		gameOverRectangleBackground.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
		window.draw(gameOverRectangleBackground);

		gameOverScoreTitle.setPosition(SCREEN_WIDTH / 2.f,
			gameOverScoreTitle.getLocalBounds().height);
		window.draw(gameOverScoreTitle);

		gameOverScores.setPosition(SCREEN_WIDTH / 2.f,
			gameOverScoreTitle.getPosition().y + gameOverScoreTitle.getLocalBounds().height);
		gameOverScores.setOrigin(gameOverScores.getLocalBounds().width / 2.f,
		gameOverScores.getLocalBounds().height / 2.f);
		window.draw(gameOverScores);
		
		gameOverRecordsTitle.setPosition(SCREEN_WIDTH / 2.f,
			gameOverScores.getPosition().y + gameOverScores.getLocalBounds().height + 100.f);
		window.draw(gameOverRecordsTitle);
		
		DrawMenuItems(window, vTextGameOverLeaderboardItems, SCREEN_WIDTH / 2.f,
			gameOverRecordsTitle.getPosition().y + gameOverRecordsTitle.getLocalBounds().height,
			35.f);
		
		DrawMenuItems(window, vTextGameOverMenuItems,
			SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 100.f * vTextGameOverMenuItems.size(), 60.f);
	}
	
	void Menu::DrawDifficultyMenu(sf::RenderWindow& window)
	{
		difficultyMenuRectangleBackground.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
		window.draw(difficultyMenuRectangleBackground);

		difficultyMenuTitle.setPosition(SCREEN_WIDTH / 2.f,
			difficultyMenuTitle.getLocalBounds().height);
		difficultyMenuTitle.setOrigin(difficultyMenuTitle.getLocalBounds().width / 2.f,
			difficultyMenuTitle.getLocalBounds().height / 2.f);
		window.draw(difficultyMenuTitle);

		DrawMenuItems(window, vTextDifficultyMenuItems,
			SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 4.f, 60.f);
	}
	
	void Menu::DrawLeaderboard(sf::RenderWindow& window)
	{
		InitLeaderboard();
		
		// Draw
		leaderboardRectangleBackground.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
		window.draw(leaderboardRectangleBackground);
		
		leaderboardTextTitle.setPosition(SCREEN_WIDTH / 2.f, 40.f);
		window.draw(leaderboardTextTitle);
			
		leaderboardTextInstructions.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 50.f);
		window.draw(leaderboardTextInstructions);

		DrawMenuItems(window, vTextLeaderboardItems,
			SCREEN_WIDTH / 2.f, 90.f, 40.f);
	}
	

	void Menu::DrawOptionsMenu(sf::RenderWindow& window)
	{
		optionsMenuRectangleBackground.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
		window.draw(optionsMenuRectangleBackground);
		
		optionsMenuTitle.setPosition(SCREEN_WIDTH / 2.f, 40.f);
		window.draw(optionsMenuTitle);

		DrawMenuItems(window, vTextOptionsMenuItems, SCREEN_WIDTH / 2.f - 50.f,
			SCREEN_HEIGHT / 4.f, 60.f);
		
		for (int i = 0; i < vRectanglesOptionsMenu.size(); i++)  // NOLINT(clang-diagnostic-sign-compare)
		{
			vRectanglesOptionsMenu[i].setOrigin
			(vRectanglesOptionsMenu[i].getLocalBounds().width,
			 vRectanglesOptionsMenu[i].getLocalBounds().height / 2.f);
			
			vRectanglesOptionsMenu[i].setPosition( SCREEN_WIDTH / 1.5f,
				vTextOptionsMenuItems[i].getPosition().y
				+ vTextOptionsMenuItems[i].getLocalBounds().height / 2.f);

			window.draw(vRectanglesOptionsMenu[i]);
		}
	}
	
	void Menu::DrawMenuItems(sf::RenderWindow& window, std::vector<sf::Text>& menuItems,
		float posX, float posY, float indentation)
	{
		float verticalIndentation = 0.f;
		for (auto& menuItem : menuItems) // NOLINT(clang-diagnostic-sign-compare)
		{
			menuItem.setPosition(posX, posY + verticalIndentation);
			window.draw(menuItem);
			verticalIndentation += indentation;
		}
	}

	void Menu::AddRecord(const std::string& playerName, int score)
	{
		// Add a new record
		VLeaderboardItems.push_back({playerName, score});
		
		// Sort vector Score Table
		std::ranges::stable_sort
		(VLeaderboardItems, [](const SLeaderboard& a, const SLeaderboard& b)
			{
				return a.score > b.score;
			}
		);
		
		// Leave only the top 10
		if (VLeaderboardItems.size() > 10)
		{
			VLeaderboardItems.pop_back();
		}

		SaveRecordsToFile(VLeaderboardItems, LEADERBOARD_FILENAME);
	}
	
	void Menu::MoveUp(std::vector<sf::Text>& menuItems)
	{
		if (selectedItemIndex > 0)
		{
			menuItems[selectedItemIndex].setFillColor(sf::Color::White);
			selectedItemIndex--;
			menuItems[selectedItemIndex].setFillColor(sf::Color::Green);
		}
	}
	
	void Menu::MoveDown(std::vector<sf::Text>& menuItems)
	{
		if (selectedItemIndex < menuItems.size() - 1)  // NOLINT(clang-diagnostic-sign-compare)
		{
			menuItems[selectedItemIndex].setFillColor(sf::Color::White);
			selectedItemIndex++;
			menuItems[selectedItemIndex].setFillColor(sf::Color::Green);
		}
	}

	void Menu::ResetMenuSelection(std::vector<sf::Text>& menuItems)
	{
		for (auto& text : menuItems)
		{
			text.setFillColor(sf::Color::White);
		}
		menuItems[selectedItemIndex].setFillColor(sf::Color::Green);
	}
	void Menu::ResetAllMenuSelection()
	{
		selectedItemIndex = 0;

		ResetMenuSelection(vTextMainMenuItems);
		ResetMenuSelection(vTextDifficultyMenuItems);
		ResetMenuSelection(vTextPauseMenuItems);
		ResetMenuSelection(vTextGameOverMenuItems);
		ResetMenuSelection(vTextOptionsMenuItems);
	}

	void Menu::SaveRecordsToFile(const std::vector<SLeaderboard>& leaderboard, const std::string& filename)
	{
		std::ofstream file(filename, std::ios::out | std::ios::trunc);
		if (file.is_open())
		{
			for (const auto& record : leaderboard)
			{
				file << record.playerName << " " << record.score << "\n";
			}
			file.close();
		}
		else
		{
			std::cerr << "Error: failed to open a record file!\n";
		}
	}

	void Menu::LoadRecordsFromFile(std::vector<SLeaderboard>& leaderboard, const std::string& filename)
	{
		std::ifstream file(filename);

		// Clean the current list before loading
		leaderboard.clear();
    
		// Check if there is a file
		if (!file)
		{
			std::ofstream createFile(filename); // Create an empty file
			if (!createFile)
			{
				std::cerr << "Error: it was not possible to create a record file!\n";
			}
			return; // The file was empty, there are no records
		}

		std::string name;
		int score;
		while (file >> name >> score)
		{
			leaderboard.push_back(SLeaderboard{name, score});
		}
		file.close();
	}

	bool Menu::IsNewRecord(const std::vector<SLeaderboard>& leaderboard, int currentScore)
	{
		// We check, if the table has less than 10 records, then the current record will always be new
		if (leaderboard.size() < 10)
		{
			return true;
		}
    
		// If the current account is greater than the lowest record (the latter in the list)
		if (currentScore > leaderboard.back().score)
		{
			return true;
		}

		return false;
	}

	void Menu::SetFillColorRectangle(int selectedIndex, bool option)
	{
		if (option)
		{
			vRectanglesOptionsMenu[selectedIndex].setFillColor(sf::Color::White);
		}
		else
		{
			vRectanglesOptionsMenu[selectedIndex].setFillColor(sf::Color::Transparent);
		}
	}
	
}

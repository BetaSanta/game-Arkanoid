#pragma once
#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 3
#define MAX_NUMBER_OF_RECORDS 10


class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow & window);
	void loseShow(sf::RenderWindow & window, int currentScore);
	void winShow(sf::RenderWindow &window, int level, int score, int bonus);
	void scoreShow(sf::RenderWindow &window, int currentScore);
	void moveUp();
	void moveDown();
	void recordsShow(sf::RenderWindow &window, float width, float height);
	void sortRecords(int *mass);
	int getPressedItem() { return selectedItemIndex; }
	void parsRecords();
	int records[MAX_NUMBER_OF_RECORDS];
	std::string recordsName[MAX_NUMBER_OF_RECORDS];
	void enterPlayerName(sf::RenderWindow &window);
	sf::Text playerName;

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text header, headerScore, headerPlayerName, footer;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	sf::Text recordsText[MAX_NUMBER_OF_RECORDS];
	sf::Text lose;
	sf::Text win;
	sf::Text score;
};


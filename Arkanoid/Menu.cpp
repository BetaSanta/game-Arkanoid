#include "Menu.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("font/pixelFont.otf"))
	{
		//handle error
	}

	header.setFont(font);
	header.setCharacterSize(50);
	header.setString("--------------------------------------------------------------\n\t\t\t\t\tARKANOID GAME\n--------------------------------------------------------------");
	header.setPosition(sf::Vector2f(0, 0));

	menu[0].setFont(font);
	menu[0].setCharacterSize(30);
	menu[0].setString("Play *");
	menu[0].setPosition(sf::Vector2f(width / 2 - 20, height / 2 - 50));

	menu[1].setFont(font);
	menu[1].setCharacterSize(30);
	menu[1].setString("Score");
	menu[1].setPosition(sf::Vector2f(width / 2 - 20, height / 2));

	menu[2].setFont(font);
	menu[2].setCharacterSize(30);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f(width / 2 - 20, height / 2 + 50));

	playerName.setFont(font);
	playerName.setCharacterSize(50);
	playerName.setString("your nickname");

	selectedItemIndex = 0;
}


Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) 
	{
		window.draw(menu[i]);
	}
	window.draw(header);
}

void Menu::loseShow(sf::RenderWindow &window, int currentScore) 
{
	lose.setFont(font);
	lose.setCharacterSize(30);
	lose.setString("\t\t\t\t\t\t\t\tYou Lose :(\n\n\n\nYou score: " + std::to_string(currentScore) + "\n\nPress 'Escape' to exit to main menu");
	lose.setPosition(sf::Vector2f(100, 100));
	window.draw(lose);
}

void Menu::winShow(sf::RenderWindow &window, int level, int score, int bonus) 
{
	win.setFont(font);
	win.setCharacterSize(30);
	win.setString("level " + std::to_string(level) + " completed\n\n\n\nYou score: " + std::to_string(score) + " +" + std::to_string(bonus) + " (bonus score)" + "\n\nPress 'space' to continue");
	win.setPosition(sf::Vector2f(100, 100));
	window.draw(win);
}

void Menu::scoreShow(sf::RenderWindow &window, int currentScore) 
{
	score.setFont(font);
	score.setCharacterSize(20);
	score.setString("Score: " + std::to_string(currentScore));
	score.setPosition(sf::Vector2f(10, 10));
	window.draw(score);
}

void Menu::recordsShow(sf::RenderWindow &window, float width, float height)
{
	headerScore.setFont(font);
	headerScore.setCharacterSize(50);
	headerScore.setString("--------------------------------------------------------------\n\t\t\t\t\tScore table\n--------------------------------------------------------------");
	headerScore.setPosition(sf::Vector2f(0, 0));

	string s1,s2;
	ifstream file1("record.txt");
	ifstream file2("recordname.txt");
	for (int i = 0; i < MAX_NUMBER_OF_RECORDS; i++)
	{
		getline(file1, s1);
		getline(file2, s2);
		if (s1 == "0")
			s1 = "---";
		recordsText[i].setFont(font);
		recordsText[i].setCharacterSize(30);
		recordsText[i].setString(std::to_string(i + 1) + ".\t" + s1 + "\t\t\t - \t\t" + s2);
		recordsText[i].setPosition(sf::Vector2f(width / 6, 200 + 25 * i));
	}
	file1.close();
	file2.close();

	for (int i = 0; i < MAX_NUMBER_OF_RECORDS; i++)
		window.draw(recordsText[i]);

	window.draw(headerScore);
}

void Menu::sortRecords(int *mass)
{
	int buf;
	for (int j = 0; j < MAX_NUMBER_OF_RECORDS; j++)
	{
		for (int i = 0; i < MAX_NUMBER_OF_RECORDS - 1; i++)
		{
			if (mass[i] > mass[i + 1])
			{
				buf = mass[i];
				mass[i] = mass[i + 1];
				mass[i + 1] = buf;
			}
		}
	}
}

void Menu::parsRecords()
{
	string s1, s2;
	ifstream file1("record.txt");
	ifstream file2("recordname.txt");

	for (int i = 0; i < MAX_NUMBER_OF_RECORDS; i++)
	{
		getline(file1, s1);
		getline(file2, s2);
		records[i] = std::stoi(s1);
		recordsName[i] = s2;
	}

	file1.close();
	file2.close();
}

void Menu::enterPlayerName(sf::RenderWindow &window) 
{
	headerPlayerName.setFont(font);
	headerPlayerName.setCharacterSize(30);
	headerPlayerName.setString("Enter please you nickname:\n\n");
	headerPlayerName.setPosition(sf::Vector2f(50, 50));

	footer.setFont(font);
	footer.setCharacterSize(15);
	footer.setString("press 'Enter' to continue \n\n");
	footer.setPosition(sf::Vector2f(300, 550));

	playerName.setFont(font);
	playerName.setCharacterSize(50);
	playerName.setPosition(sf::Vector2f(100, 200));

	window.draw(headerPlayerName);
	window.draw(playerName);
	window.draw(footer);
}

void Menu::moveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		std::string str = menu[selectedItemIndex].getString();

		menu[selectedItemIndex].setString(str.erase(str.find(" *"), 2));
		selectedItemIndex--;
		menu[selectedItemIndex].setString(menu[selectedItemIndex].getString() + " *");
	}
}

void Menu::moveDown() 
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		std::string str = menu[selectedItemIndex].getString();

		menu[selectedItemIndex].setString(str.erase(str.find(" *"), 2));
		selectedItemIndex++;
		menu[selectedItemIndex].setString(menu[selectedItemIndex].getString() + " *");
	}
}
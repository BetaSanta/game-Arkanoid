#include <SFML/Graphics.hpp>
#include <time.h>
#include "Menu.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
using namespace sf;

bool isCollide(Sprite s1, Sprite s2)
{
	return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
}

int main()
{
	srand(time(0));

	int width = 800, height = 600;

	RenderWindow window(VideoMode(width, height), "Arkanoid Game");
	window.setFramerateLimit(60);

	Menu menu(window.getSize().x, window.getSize().y);

	bool startGame = false, loseShow = false, menuShow = true, newGame = false, winShow = false, recordShow = false, isPassEnter = false;
	int currentScore = 0, bonusScore = 0;
	int level = 0;

	std::string playerName;

	Texture t1, t2, t3;
	t2.loadFromFile("images/ball.png");
	t3.loadFromFile("images/paddle.png");

	Sprite sBall(t2), sPaddle(t3);
	sBall.setPosition(width / 2, height - 35);
	sPaddle.setPosition(width / 2, height - 20);

	Sprite block[1000];

	int n = 0;
	float dx = 6, dy = 6;

	menu.parsRecords();

	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			switch (e.type)
			{
				case Event::KeyReleased:
					if (menuShow) 
					{
						switch (e.key.code)
						{
							case Keyboard::Up:
								menu.moveUp();
								break;
							case Keyboard::Down:
								menu.moveDown();
								break;
							case Keyboard::Return:
								switch (menu.getPressedItem())
								{
								case 0:
									newGame = true;
									break;
								case 1:
									recordShow = true;
									break;
								case 2:
									window.close();
									break;
								}
								break;
							case Keyboard::Escape:
								window.clear();
								currentScore = 0;
								bonusScore = 0;
								startGame = false;
								loseShow = false;
								newGame = false;
								winShow = false;
								recordShow = false;
								menuShow = true;
								break;
						}
					}
					break;
				case Event::Closed:
					window.close();
					break;
			}

			if (e.type == sf::Event::TextEntered && isPassEnter)
			{
				if (e.text.unicode < 120) 
				{
					playerName += static_cast<char>(e.text.unicode);
					menu.playerName.setString(playerName);
				}
			}

			if (Keyboard::isKeyPressed(Keyboard::BackSpace) && isPassEnter && playerName.length() > 0)
			{
				playerName.erase(playerName.end() - 1);
				menu.playerName.setString(playerName);
			}

			if(Keyboard::isKeyPressed(Keyboard::Return) && isPassEnter)
			{
				isPassEnter = false;

				if (playerName.length() == 0)
				{
					menu.playerName.setString("unknown player");
					menu.recordsName[9] = menu.playerName.getString();
				}
					

				//records
				if (menu.records[9] < currentScore + bonusScore)
				{
					menu.records[9] = currentScore + bonusScore;
					menu.recordsName[9] = menu.playerName.getString();

					int buf1;
					string buf2;
					for (int j = 0; j < MAX_NUMBER_OF_RECORDS; j++)
					{
						for (int i = 0; i < MAX_NUMBER_OF_RECORDS - 1; i++)
						{
							if (menu.records[i] < menu.records[i + 1])
							{
								buf1 = menu.records[i];
								menu.records[i] = menu.records[i + 1];
								menu.records[i + 1] = buf1;

								buf2 = menu.recordsName[i];
								menu.recordsName[i] = menu.recordsName[i + 1];
								menu.recordsName[i + 1] = buf2;
							}
						}
					}

					menu.records;
					menu.recordsName;

					ofstream fout1("record.txt");
					ofstream fout2("recordname.txt");
					for (int i = 0; i < MAX_NUMBER_OF_RECORDS; i++)
						fout1 << std::to_string(menu.records[i]) + "\n";
					for (int i = 0; i < MAX_NUMBER_OF_RECORDS; i++)
						fout2 << menu.recordsName[i] + "\n";

					fout1.close();
					fout2.close();
				}

				loseShow = true;
			}

			if (loseShow && Keyboard::isKeyPressed(Keyboard::Escape))
			{
				loseShow = false;
				menuShow = true;
			}

			if (winShow && Keyboard::isKeyPressed(Keyboard::Space))
			{
				winShow = false;
				newGame = true;
			}
		}

		// show menu
		if (menuShow)
		{
			window.clear();
			menu.draw(window);
		}

		// general random blocks and start new game
		if (newGame)
		{
			int a = rand() % 30 + 25;
			int b = rand() % 5 + 1;

			std::string str = "images/block0.png";
			std::string strB = std::to_string(b);
			str.insert(13, strB);
			t1.loadFromFile(str);
			n = 0;

			if (rand() % 3 == 1)
			{
				for (int i = 1; i <= 12; i++)
				{
					int b = rand() % 2;
					if (b == 1)
						continue;

					for (int j = 1; j <= 5; j++)
					{
						block[n].setTexture(t1);
						block[n].setPosition(i * 45 + width / 8, j * a);
						n++;
					}
				}
			}
			else
			{
				for (int i = 1; i <= 12; i++)
				{
					for (int j = 1; j <= 5; j++)
					{
						block[n].setTexture(t1);
						block[n].setPosition(i * 45 + width / 8, j * a);
						n++;
					}
				}
			}

			sBall.setPosition(width / 2, height - 35);
			sPaddle.setPosition(width / 2, height - 20);

			newGame = false;
			menuShow = false;
			startGame = true;
		}

		// start new game
		if (startGame)
		{
			
			// move ball and delete blocks
			sBall.move(dx, 0);
			for (int i = 0; i < n; i++)
			{
				if (isCollide(sBall, block[i]))
				{
					block[i].setPosition(-100, 0);
					dx = -dx;
					currentScore += 5;
				}
			}

			sBall.move(0, dy);
			for (int i = 0; i < n; i++)
			{
				if (isCollide(sBall, block[i]))
				{
					block[i].setPosition(-100, 0);
					dy = -dy;
					currentScore += 5;
				}
			}

			// move ball
			Vector2f b = sBall.getPosition();
			if (b.x < 0 || b.x > width)
				dx = -dx;
			if (b.y < 0 || b.y > height)
				dy = -dy;

			// move paddle
			if (Keyboard::isKeyPressed(Keyboard::Right) && sPaddle.getPosition().x < width - 100)
				sPaddle.move(10, 0);
			if (Keyboard::isKeyPressed(Keyboard::Left) && sPaddle.getPosition().x > 0)
				sPaddle.move(-10, 0);

			if (isCollide(sPaddle, sBall))
				dy = -(rand() % 5 + 2);

			// show lose
			if (b.y > height)
			{
				startGame = false;
				newGame = false;
				level = 0;

				if(menu.records[9] < currentScore + bonusScore)
					isPassEnter = true;
				else
					loseShow = true;
			}

			
			for (int i = 0, count = 0; i < n; i++)
			{
				if (block[i].getPosition().x == -100)
					count++;
				if (count == n)
				{
					startGame = false;
					newGame = false;
					winShow = true;
					level++;
					bonusScore += 150;
					currentScore += bonusScore;
				}
			}

			// drawing 
			window.clear();
			window.draw(sBall);
			window.draw(sPaddle);
			menu.scoreShow(window, currentScore + bonusScore);

			for (int i = 0; i < n; i++)
				window.draw(block[i]);
		}

		// enter Player nickname
		if (isPassEnter) 
		{
			window.clear();
			menu.enterPlayerName(window);
		}

		// show win
		if (winShow) 
		{
			window.clear();
			menu.winShow(window, level, currentScore, bonusScore);
		}

		// show lose
		if (loseShow)
		{
			window.clear();
			menu.loseShow(window, currentScore);
		}

		// show record table
		if(recordShow)
		{
			window.clear();
			menu.recordsShow(window, width, height);
		}

		window.display();

	}



	return 0;
}

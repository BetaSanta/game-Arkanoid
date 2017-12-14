#include "Game.h"
#include <time.h>

Game::Game(float width, float height)
{
	bool startGame = false, showLose = true;

	t1.loadFromFile("images/block02.png");
	t2.loadFromFile("images/ball.png");
	t3.loadFromFile("images/paddle.png");

	sBall.setTexture(t2);
	sPaddle.setTexture(t3);

	sPaddle.setPosition(width / 2, height - 10);
	sBall.setPosition(width / 2, height - 30);
}


Game::~Game()
{
}

bool Game::isCollide(Sprite s1, Sprite s2)
{
	return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
}

/*void Game::generalBlocks() 
{
	n = 0;
	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 10; j++) {
			block[n].setTexture(t1);
			block[n].setPosition(i * 43, j * 20);
			n++;
		}
	}
}*/

/*void Game::deleteBlocks(float dx, float dy) 
{
	// Delete blocks
	sBall.move(dx, 0);
	for (int i = 0; i < n; i++)
		if (isCollide(sBall, block[i])) {
			block[i].setPosition(-100, 0);
			dx = -dx;
		}

	sBall.move(0, dy);
	for (int i = 0; i < n; i++)
		if (isCollide(sBall, block[i])) {
			block[i].setPosition(-100, 0);
			dy = -dy;
		}
}*/

void Game::playGame(float width, float height)
{
	float dx = 5, dy = 4; // speed ball 

	// position sBall
	Vector2f b = sBall.getPosition();

	if (b.x < 0 || b.x > width)
		dx = -dx;
	if (b.y < 0 || b.y > height)
		dy = -dy;

	movePaddle(width);

	if (isCollide(sPaddle, sBall))
		dy = -(rand() % 5 + 2);
}

void Game::movePaddle(float width) 
{
	// move paddle speed=6
	if (Keyboard::isKeyPressed(Keyboard::Right) && sPaddle.getPosition().x < width - 20)
		sPaddle.move(6, 0);
	if (Keyboard::isKeyPressed(Keyboard::Left) && sPaddle.getPosition().x > 0)
		sPaddle.move(-6, 0);
}

void Game::draw(sf::RenderWindow &window)
{
	window.clear();
	window.draw(sBall);
	window.draw(sPaddle);

	// draw blocks
	for (int i = 0; i < n; i++)
		window.draw(block[i]);
}

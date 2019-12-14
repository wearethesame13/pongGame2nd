#include "Wall.h"
#include "Ball.h"
Wall::Wall()
{
	x = y = 0;
}

Wall::Wall(int posX, int posY)
{
	x = posX;
	y = posY;
}

int Wall::getX()
{
	return x;
}

int Wall::getY()
{
	return y;
}

void Wall::draw()
{
	TextColor(11);
	for (int i = 0; i < wallLength; i++)
	{
		gotoxy(x + i, y);
		cout << "x";
	}
}

bool Wall::processTouchBall(cBall* ball)
{
	if ((ball->getY() == y) ||
		(ball->getY() == y + 1 && ball->getDirection() == UP) ||
		(ball->getY() == y + 1 && ball->getDirection() == UPLEFT) ||
		(ball->getY() == y + 1 && ball->getDirection() == UPRIGHT) ||
		(ball->getY() == y - 1 && ball->getDirection() == DOWN) ||
		(ball->getY() == y - 1 && ball->getDirection() == DOWNLEFT) ||
		(ball->getY() == y - 1 && ball->getDirection() == DOWNRIGHT)) {

		if (ball->getX() < x || ball->getX() > x + wallLength - 1) return false;
		// Touched
		return true;
	}
	else return false;
}

#include "Brick.h"


Brick::Brick(int x, int y, int length, int level) :
	x(x), y(y), length(length), level(level)
{
	color[0] = 2;
	color[1] = 6;
	color[2] = 14;
}

void Brick::draw()
{
	if (level <= -1) return;

	TextColor(color[level]);
	for (int i = 0; i < length; i++) {
		gotoxy(x + i, y);
		cout << "=";
	}
}

void Brick::erase()
{
	for (int i = 0; i < length; i++) {
		gotoxy(x + i, y);
		cout << " ";
	}
}

bool Brick::processTouchBall(cBall* ball)
{
	if ((ball->getY() == y) ||
		(ball->getY() == y + 1 && ball->getDirection() == UP) ||
		(ball->getY() == y + 1 && ball->getDirection() == UPLEFT) ||
		(ball->getY() == y + 1 && ball->getDirection() == UPRIGHT) ||
		(ball->getY() == y - 1 && ball->getDirection() == DOWN) ||
		(ball->getY() == y - 1 && ball->getDirection() == DOWNLEFT) ||
		(ball->getY() == y - 1 && ball->getDirection() == DOWNRIGHT)) {

		if (ball->getX() < x || ball->getX() > x + length - 1) return false;
		// Touched
		level--;
		erase();
		if (level == -1) {
			x = y = -5;
			return true;
		}
		// Vẽ lại brick
		draw();
		return true;
	}
	else return false;
}

int Brick::getLevel()
{
	return level;
}

int Brick::getX() {
	return x;
}

int Brick::getY() {
	return y;
}

int Brick::getLenght() {
	return length;
}

int Brick::getColor() {
	return color[level];
}
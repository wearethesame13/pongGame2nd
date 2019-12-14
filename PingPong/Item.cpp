#include "Item.h"

Item::Item(int x, int y) : x(x), y(y)
{

}
int Item::getX() {
	return x;
}

int Item::getY()
{
	return y;
}

void Item::erase()
{
	gotoxy(x, y);
	cout << " ";
}

bool Item::isTouchedBall(cBall* ball)
{
	if (ball->getX() == x && ball->getY()== y)
	{
		x = -5;
		y = -5;
		return true;
	}
	return false;
}

ScoreItem::ScoreItem(int x, int y) :Item(x, y)
{
}

void ScoreItem::draw()
{
	if (x < 0) return;
	gotoxy(x, y);
	TextColor(3);
	cout << "*";
}
void ScoreItem::apply(cGameManager* game)
{
	srand(time(NULL));
	int ratio = rand() % 3 + 1;
	if (ratio == 1) {
		game->setScore(game->getScore() * 0.8);
	}
	else {
		game->setScore(game->getScore() * ratio);
	}
}

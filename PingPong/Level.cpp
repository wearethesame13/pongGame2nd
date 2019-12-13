#include "Level.h"

void TextColor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}

void gotoxy(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	_COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(hConsole, pos);
}

Level::Level(int level)
{
	current = level;
}

int Level::getLevel()
{
	return current;
}

void Level::drawStatus(int width, int height) {
	TextColor(15);
	gotoxy(width + 20, height / 2 + 1); cout << "Level: " << current;
}

void Level::levelUp()
{
	current++;
}

#include "Ball.h"


cBall::cBall (int posX, int posY) // ham constructor
{
	originalX = posX;
	originalY = posY;
	x = posX; y = posY;
	direction = STOP;
}
void cBall::Reset() // ham reset ve vi tri ban dau cua bong
{
	x = originalX; 
	y = originalY;
	direction = STOP;
}
void cBall::changeDirection(eDir d) // ham thay doi huong di cua bong
{
	direction = d;
}
void cBall::randomDirection() // ham tao huong di ngau nhien cua bong
{
	direction = (eDir)((rand() % 6) + 1); //random tu 1 den 6 vi tri
}

//ham get vi tri

int cBall::getX() 
{
	return x;
}

int cBall::getY()
{
	return y; 
}

eDir cBall::getDirection() 
{
	return direction; 
}

void cBall::Move() //ham di chuyen bong
{
	switch (direction)
	{
	case STOP:
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	case UPLEFT:
		x--; y--;
		break;
	case DOWNLEFT:
		x--; y++;
		break;
	case UPRIGHT:
		x++; y--;
		break;
	case DOWNRIGHT:
		x++; y++;
		break;
	default:
		break;
	}
}

void cBall::draw()
{
	TextColor(9);
	gotoxy(x, y);
	cout << "O";
}

//void TextColor(int x)
//{
//	HANDLE mau;
//	mau = GetStdHandle(STD_OUTPUT_HANDLE);
//	SetConsoleTextAttribute(mau, x);
//}
//
//void gotoxy(int x, int y)
//{
//	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//
//	_COORD pos;
//	pos.X = x;
//	pos.Y = y;
//
//	SetConsoleCursorPosition(hConsole, pos);
//}

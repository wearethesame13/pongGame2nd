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

void cBall::setDirection(eDir dir)
{
	direction = dir;
}

void cBall::Move() //ham di chuyen bong
{
	switch (direction)
	{
	case STOP:
		break;
	case UP:
		Delete();
		y--;
		break;
	case DOWN:
		Delete();
		y++;
		break;
	case UPLEFT:
		Delete();
		x--; y--;
		break;
	case DOWNLEFT:
		Delete();
		x--; y++;
		break;
	case UPRIGHT:
		Delete();
		x++; y--;
		break;
	case DOWNRIGHT:
		Delete();
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

void cBall::Delete()
{
	gotoxy(x, y);
	if (y == 800 / 2) { // nếu bóng ở vị trí lưới 
		TextColor(15);
		cout << static_cast<char>(176);// vẽ lại lưới 
	}
	else
		cout << " ";
}



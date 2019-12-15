#include "Paddle.h"

//dieu khien vot bong ban
cPaddle::cPaddle()
{
	x = y = 0;
}
cPaddle::~cPaddle()
{
}
cPaddle::cPaddle(int posX, int posY) : cPaddle()
{
	originalX = posX;
	originalY = posY;
	x = posX;
	y = posY;
	paddlelength = 10;
}
void cPaddle::Reset() 
{
	x = originalX; 
	y = originalY; 
} // ham reset ve vi tri ban dau cua vot

//ham get vi tri
int cPaddle::getX() 
{ 
	return x;
}
int cPaddle::getY() 
{
	return y;
}

//ham di chuyen len xuong cho vot
void cPaddle::moveUp() 
{
	y--;
}

void cPaddle::moveDown() 
{ 
	y++;
}

void cPaddle::moveLeft()
{
	Delete();
	x=x-2;
}

void cPaddle::moveRight()
{
	Delete();
	x=x+2;
}


void cPaddle::draw()
{
	TextColor(11);
	for (int i = x - paddlelength / 2; i < x + paddlelength / 2; i++) 
	{
		gotoxy(i, y);
		cout << static_cast <char>(219);
	}

}

void cPaddle::Delete()
{
	for (int i = x - paddlelength / 2; i < x + paddlelength / 2; i++)
	{
		gotoxy(i, y);
		cout << " ";
	}
}


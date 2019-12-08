#include "Wall.h"

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

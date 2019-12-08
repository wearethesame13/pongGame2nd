#include "Brick.h"

Brick::Brick()
{
	x = y = 0;
	destroyed = false;
	multiplier = 1;
}

Brick::Brick(int posX, int posY):Brick()
{
	this->x = posX;
	this->y = posY;
	destroyed = false;
	multiplier = 1;
}

Brick::~Brick()
{

}

int Brick::getX()
{
	return x;
}

int Brick::getY()
{
	return y;
}

int Brick::getMultiplier()
{
	return multiplier;
}

int Brick::setMultiplier(int a)
{
	multiplier = a;
}


bool Brick::isDestroyed()
{
	return destroyed;
}

void Brick::setDestroyed()
{
	destroyed = true;
}

void Brick::reset()
{
	destroyed = false;
}

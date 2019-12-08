#pragma once
#include "cManager.h"
class Brick
{
private: 
	int x, y;
	bool destroyed;
	int multiplier;
public:

	Brick();
	Brick(int posX, int posY);
	~Brick();
	int getX();
	int getY();
	int getMultiplier();
	int setMultiplier(int a);
	bool isDestroyed();
	void setDestroyed();
	void reset();
};


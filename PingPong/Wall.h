#pragma once
#include "Ball.h"
class Wall
{
private:
	int x, y;
public:
	int wallLength = 7;
	Wall();
	~Wall();
	Wall(int posX, int posY);
	int getX();
	int getY();
	void draw();
	bool processTouchBall(cBall* ball);
};


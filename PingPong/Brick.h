#ifndef __Brick_h__
#define __Brick_h__
#include <Windows.h>
#include "Level.h"
#include "Ball.h"


class Brick
{
private:
	int x;
	int y;
	int length;
	int level;
	int color[3];
public:
	Brick(int x, int y, int length, int level);
	~Brick();
	void draw();
	void erase();
	bool processTouchBall(cBall* ball);
	int getLevel();
	int getX();
	int getY();
	int getLenght();
	int getColor();
};
#endif // !1

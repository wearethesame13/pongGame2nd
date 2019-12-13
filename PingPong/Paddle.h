#ifndef __PADDLE_H__
#define __PADDLE_H__
#include "Ball.h"

class cPaddle
{
private:
	int x, y;    // vi tri cua vot
	int originalX, originalY; // vi tri ban dau cua vot
public:
	int paddlelength;
	cPaddle();
	cPaddle(int posX, int posY);
	void Reset();
	int getX();
	int getY();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void draw();
	void Delete();
};

#endif
#ifndef __Item_h__
#define __Item_h__
#include "Ball.h"
class cGameManager;
class Item
{
protected:
	int x;
	int y;
public:
	Item(int x, int y);
	int getX();
	int getY();
	void erase();
	bool isTouchedBall(cBall* ball);
	virtual void apply(cGameManager* game) = 0;
	virtual void draw() = 0;
};

class ScoreItem : public Item
{
public:
	ScoreItem(int x, int y);
	void draw();
	void apply(cGameManager* game);
};
#endif



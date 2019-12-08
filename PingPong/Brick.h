#ifndef __Brick_h__
#define __Brick_h__

class Brick
{
private: 
	int x;
	int y;
	bool destroyed;
	int multiplier;
public:
	Brick();
	Brick(int posX, int posY);
	~Brick();
	int getX();
	int getY();
	int getMultiplier();
	void setMultiplier(int a);
	bool isDestroyed();
	void setDestroyed();
	void reset();
};
#endif // !1

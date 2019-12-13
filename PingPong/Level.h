#pragma once
#include <vector>
#include "Brick.h"
#include <Windows.h>
#include <iostream>

using namespace std;
class Level
{
private:
	int current;
public:
	Level(int level);
	int getLevel();
	void drawStatus(int width, int height);
	void levelUp();
};

void TextColor(int x);
void gotoxy(int x, int y);

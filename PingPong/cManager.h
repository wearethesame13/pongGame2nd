#ifndef __cmanager_h__
#define __cmanager_h__

#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include "Item.h"
#include <fstream>
#include "Wall.h"
#include <windows.h>
#include <vector>

class cGameManager
{
private:
	static const int DELAY = 10;
	static const int MAX_NUMBERS_OF_WALLS = 2;
	float MULTIPLIER[3];
	int width, height; // chieu rong va chieu cao
	int score;  // diem nguoi choi
	int paddleLength;
	int wallLength;
	int brickLength;
	int speed, originalSpeed;
	bool paused;
	char left1, right1;
	bool quit;            // thoat game
	cBall * ball;
	cPaddle *player1;    // nguoi choi 1
	vector<Item*>items;
	vector<Brick*>bricks;
	Level* level;
	vector<Wall*>walls;
public:
	cGameManager();
	cGameManager(int w, int h);
	~cGameManager();
	int getSpeed();
	void setSpeed(int n);
	void LoadSavedGame();
	void SaveGame();
	void Restart();
	void renewBricks();
	void renewItems();
	void renewWall();
	void setScore(int a);
	int getScore();
	void Draw();
	void CheckInput1();
	void PrintUI(int);
	void Logic();
	void PrintResult();
	void Pause();
	void Run1();
	
};
//hàm hỗ trợ Menu lua chon nguoi choi
void Menu();
int Chon();

// hàm hỗ trợ cho background
void SetConsoleSize(int width, int height);
void removeCursor();
void WindowInit();
bool isFileEmpty(ifstream& pFile);
void clrscr();

#endif
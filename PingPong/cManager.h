#ifndef __cmanager_h__
#define __cmanager_h__

#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include <fstream>
#include "Wall.h"
#include <windows.h>
#include <vector>

class cGameManager
{
private:
	static const int MAX_NUMBERS_OF_BRICKS = 32;
	static const int DELAY = 10;
	static const int MAX_NUMBERS_OF_WALLS = 2;
	float MULTIPLIER[3];
	int width, height; // chieu rong va chieu cao
	int score;  // diem nguoi choi
	int paddleLength;
	int wallLength;
	int brickLength;
	bool paused;
	char left1, right1;
	bool quit;            // thoat game
	cBall * ball;
	cPaddle *player1;     // nguoi choi 1
	vector<Brick*>bricks;
	Level* level;
	Wall *walls;
public:
	
	cGameManager(int w, int h);
	~cGameManager();
	void LoadSavedGame();
	void Restart();
	void ScoreUp(int addScore);
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
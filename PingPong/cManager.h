#ifndef __CMANAGER_H__
#define __CMANAGER_H__
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include <fstream>
#include "Wall.h"
#include <windows.h>

class cGameManager
{
private:
	static const int MAX_NUMBERS_OF_BRICKS = 32;
	static const int DELAY = 10;
	static const int MAX_NUMBERS_OF_WALLS = 2;
	static const int MULTIPLIER[3] = { 1, 0.5, 2 };
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
	Brick* bricks[MAX_NUMBERS_OF_BRICKS];
	Wall* walls[MAX_NUMBERS_OF_WALLS];
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
void gotoxy(int x, int y);
void TextColor(int x);
void WindowInit();
bool isFileEmpty(ifstream& pFile);

#endif
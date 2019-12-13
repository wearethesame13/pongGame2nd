#include"cManager.h"

void SetConsoleSize(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void clrscr()
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = { 0,0 };
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}

void removeCursor()
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}


void WindowInit()
{
	SetConsoleSize(800, 480);
	removeCursor();
}

bool isFileEmpty(ifstream& pFile)
{
	return pFile.peek() == ifstream::traits_type::eof();
}

// quan ly luat choi, diem so
cGameManager::cGameManager(int w, int h)
{
	srand((unsigned int)time(NULL)); // thoi gian ngau nhien
	quit = false;
	left1 = 'a'; right1 = 'd';
	score = 0;   // set diem ca 2 player = 0
	width = w; height = h;
	MULTIPLIER[0] = 1;
	MULTIPLIER[1] = 0.5;
	MULTIPLIER[2] = 2;
	level = new Level(1);
	bricks.resize(0);
	//items.resize(0);
	walls = new Wall[MAX_NUMBERS_OF_WALLS];
	paddleLength = 10;
	wallLength = 10;
	brickLength = 5;
	paused = false;
	ball = new cBall(w / 2, h / 2);  //dat Ball o chinh giua ban
	player1 = new cPaddle(w/2, h-2); //dat vi tri ban dau cua vot player 1
	srand(time(NULL));
	for (int i = 3; i <= 7; i++)
	{
		if (i % 2 == 0) continue;
		for (int j = 3; j < width - 8; j += 8)
		{
			int isBrickCreate = rand() % 2;
			if (isBrickCreate == 0) continue;

			// random brickLevel
			int brickLevel;

			if (level->getLevel() == 1) brickLevel = rand() % 1;
			else if (level->getLevel() == 2) brickLevel = rand() % 2;
			else brickLevel = rand() % 3;

			Brick* newBrick = new Brick(j, i, 7, brickLevel);
			bricks.push_back(newBrick);
		}
	}
	
}

cGameManager::~cGameManager()
{
	delete ball, player1;
	for (int i = 0; i < MAX_NUMBERS_OF_BRICKS; i++)
	{
		bricks[i]->~Brick();
	}
}
void cGameManager::LoadSavedGame()
{
	ifstream fileIn("SaveGame.txt", ios::in);
	if (isFileEmpty(fileIn)==true)
	{
		return;
	}
	else
	{
		
	}
}
void cGameManager::Restart()
{
	system("cls");
	ball->Reset();
	player1->Reset();
	TextColor(0);
	Draw();
}
//ham tinh diem
void cGameManager::ScoreUp(int addScore)
{
	score += addScore;	
}

//ve vi tri cho bong va vot
void cGameManager::Draw()
{
	gotoxy(0, 0);
	TextColor(11);
	// tao khung tro choi
	int color = 13;
	TextColor(color);
	//Biên trái
	for (int i = 0; i <= height; i++)
	{
		gotoxy(0, i);
		cout << static_cast<char>(219);
	}
	//Biên phải
	for (int i = 0; i <= height; i++)
	{
		gotoxy(width, i);
		cout << static_cast<char>(219);

	}
	//Biên trên
	for (int i = 1; i < width; i++)
	{
		gotoxy(i, 0);
		cout << static_cast<char>(219);
	}
	//Biên dưới
	for (int i = 1; i < width; i++)
	{
		gotoxy(i, height);
		cout << static_cast<char>(219);
	}

	for (int i = 0; i < bricks.size(); i++)
	{
		bricks[i]->draw();
	}

	ball->draw();
	cout << endl;
	player1->draw();

	for (int i = 0; i < bricks.size(); i++)
	{
		if (!bricks[i]->processTouchBall(ball)) continue;
		score++;
		//Xoá gạch khỏi list
		if (bricks[i]->getLevel() < 0) {
			bricks.erase(bricks.begin() + i);
			bricks.shrink_to_fit();
		}
		// Ball touch brick
		// Bóng đang đi lên
		if (ball->getDirection() == UP) {
			int ran = rand() % 3 + 4;
			if (ran == 4)
				ball->setDirection(DOWN);
			else if (ran == 5)
				ball->setDirection(DOWNLEFT);
			else if (ran == 6)
				ball->setDirection(DOWNRIGHT);
		}
		else if (ball->getDirection() == UPLEFT)
			ball->setDirection(DOWNLEFT);
		else if (ball->getDirection() == UPRIGHT)
			ball->setDirection(DOWNRIGHT);
		// Bóng đang đi xuống
		else if (ball->getDirection() == DOWN) {
			int ran = rand() % 3 + 4;
			if (ran == 4)
				ball->setDirection(UP);
			else if (ran == 5)
				ball->setDirection(UPLEFT);
			else if (ran == 6)
				ball->setDirection(UPRIGHT);
		}
		else if (ball->getDirection() == DOWNLEFT)
			ball->setDirection(UPLEFT);
		else if (ball->getDirection() == DOWNRIGHT)
			ball->setDirection(UPRIGHT);
	}
}

void  cGameManager::CheckInput1()
{
	ball->Move(); //di chuyen bong

	// lay toa do cua ball va player
	int ballx = ball->getX();
	int bally = ball->getY();
	int player1x = player1->getX();
	int player1y = player1->getY();

	if (_kbhit())
	{
		char current = _getch(); //nhan du lieu 
		if (current == left1)
		if (player1x - paddleLength / 2 > 0)
			player1->moveLeft();

		if (current == right1)
		if (player1x + paddleLength / 2 < width-1)
			player1->moveRight();

		if (ball->getDirection() == STOP) //neu ball dung lai thi tao vi tri ngau nhien cho ball
			ball->randomDirection();

		if (current == 'q') //quit game
			quit = true;
		if (current == 'esc') // pause game
		{
			paused = true;
		}
	}

}

void  cGameManager::PrintUI(int choose)
{
	TextColor(10);
	gotoxy(width + 5, 5);
	cout << "Player's score: " << score;
	TextColor(12);
	gotoxy(width + 5, 8);
	cout << "Press Q key to quit game"<<endl;
	TextColor(11);
	gotoxy(width + 5, 9);
	cout << "Press ESC key to pause game";
	gotoxy(width / 2 - 7, height + 3);
	TextColor(10); cout << "Brick"; TextColor(11); cout << " Breaker"; TextColor(12); cout << " GAME";
	gotoxy(width / 2 - 8, height + 4);
}

void cGameManager::PrintResult()
{
	//Win-Lose
	system("cls");
	cout << "YOU WIN!!" << endl;
	system("pause");
	quit = true;
}

void cGameManager::Pause()
{
	if (paused == true)
	{
		gotoxy(width + 5, 6);
		TextColor(12);
		cout << "Game tam dung, nhan Enter de tiep tuc choi";
		TextColor(0);
		system("pause");
	}
}

//ham va cham bong
void cGameManager::Logic()
{
	// lay toa do cua ball va player
	int ballx = ball->getX();
	int bally = ball->getY();
	int player1x = player1->getX();
	int player1y = player1->getY();
	if (bally == player1y -1)   //neu ball canh benh player
	if (ballx >= player1x - paddleLength/2 && ballx <= player1x +paddleLength/2)
		//ball->changeDirection((eDir)((rand() % 3) + 4)); //chuyen huong bong sang vi tri ngau nhien qua phai
		ball->changeDirection(ball->getDirection() == DOWNLEFT ? UPLEFT : UPRIGHT);
	//top wall
	if (bally == 0)
		ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
	//right wall
	if (ballx == width - 1)
		ball->changeDirection(ball->getDirection() == UPRIGHT ? UPLEFT : DOWNLEFT);
	//left wall
	else if (ballx == 0)
		ball->changeDirection(ball->getDirection() == UPLEFT ? UPRIGHT : DOWNRIGHT);


	
}

void Menu()
{
	system("cls");
	cout << "======================= MENU =====================\n\n";
	cout << "Chao mung ban den voi game Pha Gach" << endl;
	cout << "1. Bat dau choi." << endl;
	cout << "2. Thoat." << endl;
	cout << "==================================================\n";
}

int Chon()
{
	int lenh;

	cout << "\n Nhap lua chon cua ban: ";
	cin >> lenh;
	if (lenh < 1 || lenh > 2)
	{
		cout << "\nLua chon khong hop le. Xin kiem tra lai !\n";
		system("pause");
		exit(0);
	}
	return lenh;
}

void cGameManager::Run1()
{
	Draw();
	PrintUI(1);

	while (!quit)
	{
		srand((unsigned int)time(NULL));
		CheckInput1();
		Logic();
		Draw();
		PrintUI(1);
		Sleep(100);
		//PrintResult();
		Pause();
	}
	
}


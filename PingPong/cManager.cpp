#include"cManager.h"

void SetConsoleSize(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void removeCursor()
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void gotoxy(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	_COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(hConsole, pos);
}

void TextColor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
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
	paddleLength = 10;
	wallLength = 10;
	brickLength = 5;
	paused = false;
	ball = new cBall(w / 2, h / 2);  //dat Ball o chinh giua ban
	player1 = new cPaddle(w/2, h-2); //dat vi tri ban dau cua vot player 1
	int k = 0;
	for (int i = 0; i < 4; i++) // khoi tao day brick
	{
		for (int j = 0; j < 8; j++)
		{
			bricks[k] = new Brick(j * brickLength, i*2);
			srand((unsigned)time(0));
			int a;
			a = (rand() % 3) + 1;
			bricks[i]->setMultiplier(a);
			k++;
		}
	}
	
}

cGameManager::~cGameManager()
{
	delete ball, player1;
	for (int i = 0; i < MAX_NUMBERS_OF_BRICKS; i++)
	{
		delete bricks[i];
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
	for (int i = 0; i < width + 2; i++)
		cout << "\xB2";
	TextColor(0);
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			// lay toa do cua ball va player
			int ballx = ball->getX();
			int bally = ball->getY();
			int player1x = player1->getX();
			int player1y = player1->getY();
			if (j == 0)
			{
				TextColor(11);
				cout << "\xB2"; //ve khung ben trai
				TextColor(0);
			}
			for (int i = 0; i < MAX_NUMBERS_OF_BRICKS; i++) //ve gach
			{
				if (bricks[i]->isDestroyed()==true)
				{
					continue;
				}
				int brickx = bricks[i]->getX();
				int bricky = bricks[i]->getY();
				if ((i == bricky && j >= brickx - brickLength / 2 && j <= brickx + brickLength / 2))
				{
					TextColor(11);
					cout << "\xDB";
					TextColor(0);
				}
			}
			if (ballx == j && bally == i)
			{
				TextColor(11);
				cout << "O"; //ball   #ve vi tri bong
				TextColor(0);
			}
			
			else if (i == player1y && j >= player1x-paddleLength/2 && j <= player1x + paddleLength/2)
			{
				TextColor(11);
				cout << "\xDB"; //player   //ve vi tri nguoi choi 
				TextColor(0);
			}
			else
				cout << " ";

			if (j == width - 1)  //ve khung ben phai
			{
				TextColor(11);
				cout << "\xB2"; //ve khung ben phai
				TextColor(0);
			}
		}
		cout << endl;
	}

	TextColor(11);
	for (int i = 0; i < width + 2; i++) // ve khung duoi
		cout << "\xB2";
	TextColor(0);
	cout << endl;
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
	for (int i = 0; i < MAX_NUMBERS_OF_BRICKS; i++)
	{
		int brickx = bricks[i]->getX();
		int bricky = bricks[i]->getY();
		if (bally == bricky - 1)
		{
			if (ballx >= brickx - brickLength / 2 && ballx <= brickx + brickLength / 2)
			{
				ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
				bricks[i]->setDestroyed();
			}
		}
	}
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
		PrintResult();
		Pause();
	}
	
}

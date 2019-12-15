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
cGameManager::cGameManager() {
	width = 0;
	height = 0;
	score = 0;
	player1 = new cPaddle(width / 2 - 4, height - 1);
	ball = new cBall(width / 2 + 1, height - 2);
	quit = false;

	bricks.resize(0);
	items.resize(0);
	walls.resize(0);
}
cGameManager::cGameManager(int w, int h)
{
	srand((unsigned int)time(NULL)); // thoi gian ngau nhien
	quit = false;
	left1 = 'a'; right1 = 'd';
	score = 0;   // set diem player = 0
	width = w; height = h;
	level = new Level(2);
	bricks.resize(0);
	//items.resize(0);
	paddleLength = 10;
	brickLength = 5;
	paused = false;
	ball = new cBall(w / 2, h / 2);  //dat Ball o chinh giua ban
	player1 = new cPaddle(w/2, h-2); //dat vi tri ban dau cua vot player 1
	srand(time(NULL));
	//tao vector bricks
	for (int i = 3; i <= 7; i++)
	{
		if (i % 3 == 0) {
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
	srand(time(NULL));

	for (int i = 3; i <= 9; i++)
	{
		if (i % 3 == 1) {
			for (int j = 6; j < width - 8; j += 8)
			{
				int isItemCreate = rand() % 5;
				if (isItemCreate < 4) continue;

				Item* newItem;
				newItem = new ScoreItem(j, i);
				items.push_back(newItem);
			}
		}
	}
	for (int i = 3; i <= 10; i++)
	{
		for (int j = 6; j < width - 10; j += 8)
		{
			if (i % 3 == 2) {

				int isWallCreate = rand() % 6;
				if (isWallCreate < 5) continue;
				Wall* newWall;
				newWall = new Wall(j, i);
				walls.push_back(newWall);
				if (walls.size() == MAX_NUMBERS_OF_WALLS)
				{
					return;
				}
			}
			
		}
	}
}

cGameManager::~cGameManager()
{
	delete ball, player1;
	for (int i = 0; i < bricks.size(); i++)
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
		quit = false;
		int ballX, ballY;
		int paddleX, paddleY;
		int len;
		int LV = 1;
		int dir;
		fileIn >> ballX;
		fileIn >> ballY;
		fileIn >> dir;
		fileIn >> paddleX;
		fileIn >> paddleY;
		if (player1!=NULL)
		{
			delete player1;
		}
		player1 = new cPaddle(paddleX, paddleY);
		if (ball!=NULL)
		{
			delete ball;
		}
		ball = new cBall(ballX, ballY);
		ball->setDirection((eDir)dir);
		int numBricks;
		fileIn >> numBricks;
		int brickX, brickY;
		for (int i = 0; i < numBricks; i++)
		{
			Brick* brick;
			fileIn >> brickX;
			fileIn >> brickY;
			fileIn >> len;
			fileIn >> LV;
			brick = new Brick(brickX, brickY, len, LV);
			bricks.push_back(brick);
		}
		int itemNums;
		fileIn >> itemNums;
		int itemX, itemY;
		for (int i = 0; i < itemNums; i++)
		{
			Item* item;
			fileIn >> itemX;
			fileIn >> itemY;
			item = new ScoreItem(itemX, itemY);
			items.push_back(item);
		}
		int wallNums;
		fileIn >> wallNums;
		int wallX, wallY;
		for (int i = 0; i < wallNums; i++)
		{
			Wall* wall;
			fileIn >> wallX;
			fileIn >> wallY;
			wall = new Wall(wallX, wallY);
			walls.push_back(wall);
		}
	}
	fileIn.close();
}
void cGameManager::SaveGame()
{
	ofstream fileOut;
	fileOut.open("SaveGame.txt", ios::trunc);
	if (!fileOut.is_open())
	{
		cout << "Can not open file";
		Sleep(2000);
		return;
	}

	int dir;
	fileOut << ball->getX()<< endl;
	fileOut << ball->getY() << endl;
	fileOut << ((int)ball->getDirection()) << endl;
	fileOut << player1->getX() << endl;
	fileOut << player1->getY() << endl;
	fileOut << bricks.size();
	for (int i = 0; i < bricks.size(); i++)
	{
		fileOut << bricks[i]->getX() << endl;
		fileOut << bricks[i]->getY() << endl;
		fileOut << bricks[i]->getLenght() << endl;
		fileOut << bricks[i]->getLevel() << endl;
	}
	fileOut << items.size();
	for (int i = 0; i < items.size(); i++)
	{
		fileOut << items[i]->getX() << endl;
		fileOut << items[i]->getY() << endl;
	}
	fileOut << walls.size();
	for (int i = 0; i < walls.size(); i++)
	{
		fileOut << walls[i]->getX() << endl;
		fileOut << walls[i]->getY() << endl;

	}
	fileOut.close();
}
void cGameManager::Restart()
{
	system("cls");
	quit = false;
	ball->Reset();
	player1->Reset();
	renewBricks();
	renewItems();
	renewWall();
	TextColor(0);
}
void cGameManager::renewBricks()
{
	bricks.clear();
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
void cGameManager::renewItems()
{
	items.clear();
	for (int i = 3; i <= 9; i++)
	{
		if (i % 3 == 1) {
			for (int j = 6; j < width - 8; j += 8)
			{
				int isItemCreate = rand() % 5;
				if (isItemCreate < 4) continue;

				Item* newItem;
				newItem = new ScoreItem(j, i);
				items.push_back(newItem);
			}
		}
	}
}
void cGameManager::renewWall()
{
	walls.clear();
	for (int i = 3; i <= 10; i++)
	{
		for (int j = 6; j < width - 10; j += 8)
		{
			int isWallCreate = rand() % 7;
			if (isWallCreate < 6) continue;
			
			Wall* newWall;
			newWall = new Wall(j, i);
			walls.push_back(newWall);
		}
	}
}
//ham tinh diem
void cGameManager::setScore(int a)
{
	score = a;
}
int cGameManager::getScore()
{
	return score;
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
	//Ve gach
	for (int i = 0; i < bricks.size(); i++)
	{
		bricks[i]->draw();
	}
	//Ve item
	for (int i = 0; i < items.size(); i++)
	{
		items[i]->draw();
	}
	for (int i = 0; i < walls.size(); i++)
	{
		walls[i]->draw();
	}
	ball->draw();
	cout << endl;
	player1->draw();
	//Ball cham gach
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
		if (player1x - paddleLength / 2 > 1)
			player1->moveLeft();

		if (current == right1)
		if (player1x + paddleLength / 2 < width-1)
			player1->moveRight();

		if (ball->getDirection() == STOP) //neu ball dung lai thi tao vi tri ngau nhien cho ball
			ball->randomDirection();

		if (current == 'p' || current == 'P') //pause
			paused = true;
		if (current == '\e')
		{
			quit = true;
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
	cout << "Press ESC key to quit game"<<endl;
	TextColor(11);
	gotoxy(width + 5, 9);
	cout << "Press P key to pause game";
	gotoxy(width / 2 - 7, height + 3);
	TextColor(10); 
	cout << "Brick";
	TextColor(11); 
	cout << " Breaker"; 
	TextColor(12); 
	cout << " GAME";
	gotoxy(width / 2 - 8, height + 4);
}

void cGameManager::PrintResult()
{
	//Win-Lose
	system("cls");
	cout << "YOUR SCORES: " << score << endl;
	fstream fileout;
	fileout.open("HighScore.txt", ios::app);
	fileout << score << endl;
	fileout.close();

	fstream filein;
	filein.open("HighScore.txt", ios::in);
	vector<int>scores;
	int x;
	while (filein.eof()==false)
	{
		filein >> x;
		scores.push_back(x);
	}
	int max = scores[0];
	for (int i = 1; i < scores.size(); i++)
	{
		if (max < scores[i])
		{
			max = scores[i];
		}
	}
	cout << "HIGHSCORE IS: " << max << endl;
}

void cGameManager::Pause()
{
	system("cls");
	TextColor(12);
	cout << "Game tam dung!!!" << endl;
	TextColor(11);
	cout<<"1. Choi tiep."<<endl;
	TextColor(10);
	cout << "2. Luu va thoat game."<<endl;
	TextColor(0);
	int choose;
	choose = Chon();
	if (choose==1)
	{
		paused = false;
	}
	if (choose==2)
	{
		SaveGame();
		quit = true;
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
	if (bally == 1)
		ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
	//right wall
	if (ballx == width - 1)
		ball->changeDirection(ball->getDirection() == UPRIGHT ? UPLEFT : DOWNLEFT);
	//left wall
	else if (ballx == 1)
		ball->changeDirection(ball->getDirection() == UPLEFT ? UPRIGHT : DOWNRIGHT);

	//Neu gach het thi tao vector gach moi
	if (bricks.empty() == true)
	{
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
	if (items.empty() == true)
	{
		for (int i = 3; i <= 7; i++)
		{
			if (i % 2 == 0) continue;
			for (int j = 3; j < width - 8; j += 8)
			{
				int isItemCreate = rand() % 2;
				if (isItemCreate == 0) continue;

				
				Item* newItem = new ScoreItem(j, i);
				items.push_back(newItem);
			}
		}
	}
	// Xuat diem player
	if (ball->getY() == height)
	{
		quit = true;
	}
	for (int i = 0; i < (int)items.size(); i++)
	{
		if (!items[i]->isTouchedBall(ball)) continue;
		// Touched
		items[i]->apply(this);
		items.erase(items.begin() + i);
		items.shrink_to_fit();
	}
	for (int i = 0; i < (int)walls.size(); i++)
	{
		if (!walls[i]->processTouchBall(ball))
		{
			continue;
		}
		//Touched
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

void Menu()
{
	system("cls");
	
	cout << "======================= MENU =====================\n\n";
	cout << "Chao mung ban den voi game Pha Gach" << endl;
	cout << "1. Start." << endl;
	cout << "2. Resume" << endl;
	cout << "2. Exit." << endl;
	cout << "==================================================\n";
}

int Chon()
{
	int lenh;

	cout << "\n Nhap lua chon cua ban: ";
	cin >> lenh;
	if (lenh < 1 || lenh > 3)
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

	while (true && quit!= true)
	{
		srand((unsigned int)time(NULL));
		CheckInput1();
		
		Logic();
		Draw();
		PrintUI(1);
		if (paused == true)
		{
			Pause();
		}
		Sleep(100);
	}
	PrintResult();
	cout << "1. Choi lai" << endl;
	cout << "2. Thoat" << endl;
	int choose;
	choose = Chon();
	if (choose==1)
	{
		Restart();
		Run1();
	}
	if (choose==2)
	{
		return;
	}
}

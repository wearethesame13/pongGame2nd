#pragma once
#include "Ball.h"
#include "cManager.h"
#include "Paddle.h"

int main()
{
	int choose = 0;

	Menu();
	choose = Chon();
	system("cls");
	WindowInit();
	
	if (choose == 1) {
		cGameManager c(40, 20);
		c.Run1();
	}
	if (choose == 2)
	{
		cGameManager c(40, 20);
		c.LoadSavedGame();
		c.Run1();
	}
	if (choose == 3)
		return EXIT_SUCCESS;
	system("pause");
	return 0;
}
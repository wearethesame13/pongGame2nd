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
	cGameManager c(40, 20);
	if (choose == 1)
		c.Run1();
	else
		return EXIT_SUCCESS;
	system("pause");
	return 0;
}
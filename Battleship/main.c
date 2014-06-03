#include "stdafx.h"
#include "move.h"

int main(int argc, char *argv[])
{
	int isGameOver = 0;
	Tile gridP1[10][10], gridP2[10][10];
	Boat boatsP1[5], boatsP2[5];
	
	printf("-----------------BATTLESHIP-----------------\n\n");
	/*Grid initialisation*/
	setGrid(gridP1, boatsP1, 1);
	setGrid(gridP2, boatsP2, 2);

	/*Main game*/
	firstMove();
	while (isGameOver == 0)
	{
		isGameOver = playerMove(gridP1, gridP2, boatsP2, 1);
		if (isGameOver == 0) { isGameOver = playerMove(gridP2, gridP1, boatsP1, 2); }
	}

	getchar();
	return 0;
}
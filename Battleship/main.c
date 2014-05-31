#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"

int main(int argc, char *argv[])
{
	Tile gridP1[10][10], gridP2[10][10];
	Boat boatsP1[5], boatsP2[5];

	printf("-----------------BATTLESHIP-----------------\n\n");
	setGrid(gridP1, boatsP1, 1);
	setGrid(gridP2, boatsP2, 2);
	system("pause");
	return 0;
}
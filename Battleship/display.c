#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"

void displayGrid(Tile grid[][10], gridType displayType)
{
	int i, posX;
	char posY;
	
	printf("\n   ");
	for (posX = 0; posX <= 9; posX++) { printf("| %d ", posX); }
	printf("|\n");
	for (i = 1; i <= 44; i++) { printf("-"); }
	printf("\n");

	
	if (displayType == pers)
	{
		for (posY = 'A'; posY <= 'J'; posY++)
		{
			printf(" %c ", posY);
			for (posX = 0; posX <= 9; posX++) { printf("| %c ", grid[posX][posY-65].statePers); }
			printf("|\n");
			for (i = 1; i <= 44; i++) { printf("-"); }
			printf("\n");
		}
	}
	else if (displayType == enemy)
	{
		for (posY = 'A'; posY <= 'J'; posY++)
		{
			printf(" %c ", posY);
			for (posX = 0; posX <= 9; posX++) { printf("| %c ", grid[posX][posY-65].stateEnemy); }
			printf("|\n");
			for (i = 1; i <= 44; i++) { printf("-"); }
			printf("\n");
		}
	}
}

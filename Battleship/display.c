#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"

/*Procedure displayGrid : displays the player grid, from the player's view (pers), or from the enemy's view(enemy)*/
void displayGrid(Tile grid[][10], gridType displayType)
{
	int i, posX;
	char posY;
	
	/*Displaying the 1st line with the x coordinates*/
	printf("\n   ");
	for (posX = 0; posX <= 9; posX++) { printf("| %d ", posX); }
	printf("|\n");
	for (i = 1; i <= 44; i++) { printf("-"); }
	printf("\n");

	/*Displays each line, with the y coordinate, and the state of each case (statePers if personal display, stateEnemy if enemy display)*/
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

	printf("\n");
}

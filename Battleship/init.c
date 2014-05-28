#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"

void exchange(char *var1, char *var2)
{
	char varTmp = *var1;
	*var1 = *var2;
	*var2 = varTmp;
}

void initGrid(Tile grid[][10])
{
	int posX, posY;

	for (posX = 0; posX <= 9; posX++)
	{
		for (posY = 0; posY <= 9; posY++)
		{
			grid[posX][posY].statePers = 0;
			grid[posX][posY].stateEnemy = 0;
		}
	}
}
#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"

void exchange(char *var1, char *var2)
{
	*var1 = *var1 + *var2; // a = a0 + b0
	*var2 = *var1 - *var2; // b = a - b = a0 + b0 - b0 = a0
	*var1 = *var1 - *var2; // a = a - b = a0 + b0 - a0 = b0
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
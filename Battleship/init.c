#include "stdafx.h"

/*Procedure exchangeChr : exchanges two variables of char type.*/
void exchangeChr(char *var1, char *var2)
{
	*var1 = *var1 + *var2;
	*var2 = *var1 - *var2;
	*var1 = *var1 - *var2;
}

/*Procedure removeLastChar : Removes the last character from a string.*/
void removeLastChar(char str[])
{
	char *pointer;
	pointer = str;
	pointer[strlen(pointer) - 1] = 0;
}

/*Procedure initGrid : sets the state of each tile of the grid to 0*/
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
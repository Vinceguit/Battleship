#define _CRT_SECURE_NO_DEPRECATE
#define MAX_SIZE 200
#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"

void setGrid(Tile playerGrid[][10], Boat boatGrid[])
{
	char confirm = 'n';

	while (confirm == 'n' || confirm == 'N')
	{
		placeBoats(playerGrid, boatGrid, 2, 0);
		placeBoats(playerGrid, boatGrid, 3, 1);
		placeBoats(playerGrid, boatGrid, 3, 2);
		placeBoats(playerGrid, boatGrid, 4, 3);
		placeBoats(playerGrid, boatGrid, 5, 4);

		do
		{
			printf("Do you want to confirm and keep this grid ? y/n ");
			scanf("%c", &confirm);
		} while (confirm != 'y' && confirm != 'n' && confirm != 'Y' && confirm != 'N');

		if (confirm == 'n' || confirm == 'N') { initGrid(playerGrid); }
	}
}

static void placeBoats(Tile playerGrid[][10], Boat boatGrid[], int boatSize, int boatId)
{
	FILE *interfaceText = NULL;
	int i, isBoatSizeWrong = 1, isBoatOverriding = 0;
	char str[200];
	Tile pos1, pos2;
	pos1.x = 1; pos1.y = 2; pos2.x = 3; pos2.y = 4;

	boatGrid[boatId].size = boatSize;
	boatGrid[boatId].isSunk = 0;

	interfaceText = fopen("interface.txt", "r");
	if (interfaceText != NULL)
	{
		do
		{
			rewind(interfaceText);
			for (i = 0; i <= 3; i++) 
			{ 
				fgets(str, MAX_SIZE, interfaceText);
			}

			isBoatSizeWrong = 0;

			printf(str, boatSize);

			if (pos1.x == pos2.x)
			{
				isBoatOverriding = testOverride_xStatic(playerGrid, boatGrid, pos1, pos2, boatId);
			}
			else if (pos1.y == pos2.y)
			{
				isBoatOverriding = testOverride_yStatic(playerGrid, boatGrid, pos1, pos2, boatId);
			}

		} while (isBoatOverriding == 1);

		fclose(interfaceText);
	}
	else
	{
		printf("An error occured while loading interface.txt @ function placeBoats. Boat ID : %d\n", boatId);
	}
}
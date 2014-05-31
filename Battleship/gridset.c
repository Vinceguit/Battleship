#define _CRT_SECURE_NO_DEPRECATE
#define MAX_SIZE 200
#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"
#include "override.h"

void setGrid(Tile playerGrid[][10], Boat boatGrid[], int playerId)
{
	char confirm = 'n';
	FILE *interfaceText = NULL;
	interfaceText = fopen("interface.txt", "r");

	if (interfaceText != NULL)
	{
		while (confirm == 'n' || confirm == 'N')
		{
			initGrid(playerGrid);
			displayGrid(playerGrid, pers);
			placeBoats(playerGrid, boatGrid, interfaceText, 2, 0);
			placeBoats(playerGrid, boatGrid, interfaceText, 3, 1);
			placeBoats(playerGrid, boatGrid, interfaceText, 3, 2);
			placeBoats(playerGrid, boatGrid, interfaceText, 4, 3);
			placeBoats(playerGrid, boatGrid, interfaceText, 5, 4);

			do
			{
				printf("Do you want to confirm and keep this grid ? y/n ");
				scanf("%c", &confirm);
			} while (confirm != 'y' && confirm != 'n' && confirm != 'Y' && confirm != 'N');

			if (confirm == 'n' || confirm == 'N') { initGrid(playerGrid); }
		}
	}
	else
	{
		printf("An error occured while loading interface.txt");
	}

	fclose(interfaceText);
}

static void placeBoats(Tile playerGrid[][10], Boat boatGrid[], FILE *interfaceText, int boatSize, int boatId)
{
	int i, isInputInvalid, isBoatSizeWrong, isBoatOverriding = 1;
	char purge, *pText, text[2][MAX_SIZE], error[3][MAX_SIZE];
	Tile pos1, pos2;

	boatGrid[boatId].size = boatSize;
	boatGrid[boatId].isSunk = 0;
	
	while (isBoatOverriding != 0)
	{
		isBoatSizeWrong = 1;

		rewind(interfaceText);
		for (i = 0; i <= 3; i++) { fgets(text[0], MAX_SIZE, interfaceText); }
		fgets(error[0], MAX_SIZE, interfaceText);
		fgets(error[1], MAX_SIZE, interfaceText);
		fgets(error[2], MAX_SIZE, interfaceText);
		fgets(text[1], MAX_SIZE, interfaceText);

		pText = text[0];
		pText[strlen(pText) - 1] = 0;

		while (isBoatSizeWrong != 0)
		{
			isInputInvalid = 1;
			while (isInputInvalid != 0)
			{
				printf(text[0], boatSize);
				scanf("%c%c %c%c", &pos1.y, &pos1.x, &pos2.y, &pos2.x);
				while (purge = _fgetchar(), purge != '\n' && purge != EOF);
				pos1.x = pos1.x - 48;
				pos2.x = pos2.x - 48;
				pos1.y = pos1.y - 65;
				pos2.y = pos2.y - 65;
				printf("\n");

				if ((0 <= pos1.y) && (pos1.y <= 9) && (0 <= pos1.x) && (pos1.x <= 9) && (0 <= pos2.y) && (pos2.y <= 9) && (0 <= pos2.x) && (pos2.x <= 9))
				{
					isInputInvalid = 0;
				}
				else
				{
					printf(error[0]);
				}
			}

			if (((pos1.x == pos2.x) && (abs(pos2.y - pos1.y) + 1 == boatSize)) || ((pos1.y == pos2.y) && (abs(pos2.x - pos1.x) + 1 == boatSize)))
			{
				isBoatSizeWrong = 0;
			}
			else
			{
				printf(error[1]);
			}
		}

		if (pos1.x == pos2.x)
		{
			isBoatOverriding = testOverride_xStatic(playerGrid, boatGrid, pos1, pos2, boatId);
		}
		else if (pos1.y == pos2.y)
		{
			isBoatOverriding = testOverride_yStatic(playerGrid, boatGrid, pos1, pos2, boatId);
		}

		if (isBoatOverriding == 0)
		{
			printf(text[1]);
			displayGrid(playerGrid, pers);
		}
		else
		{
			printf(error[2]);
		}
	}
}
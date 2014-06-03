#include "stdafx.h"
#include "override.h"

/*Procedure setGrid : initialises, reads the boats positions, and asks for confirmation*/
void setGrid(Tile playerGrid[][10], Boat boatGrid[], int playerId, FILE *interfaceText)
{
	char  purge, i, textMain[2][MAX_SIZE], confirm = 'n';

	/*Reading all the interface messages from the file*/
	rewind(interfaceText);
	fgets(textMain[0], MAX_SIZE, interfaceText);
	for (i = 1; i <= 7; i++) { fgets(textMain[1], MAX_SIZE, interfaceText); }
	removeLastChar(textMain[1]);

	printf(textMain[0], playerId);

	while (confirm == 'n' || confirm == 'N')
	{
		/*Initialisation and display of each grid*/
		initGrid(playerGrid);
		displayGrid(playerGrid, pers);

		/*Placement of each boat*/
		placeBoats(playerGrid, boatGrid, interfaceText, 2, 0);
		placeBoats(playerGrid, boatGrid, interfaceText, 3, 1);
		placeBoats(playerGrid, boatGrid, interfaceText, 3, 2);
		placeBoats(playerGrid, boatGrid, interfaceText, 4, 3);
		placeBoats(playerGrid, boatGrid, interfaceText, 5, 4);

		/*Confirmation of the grid + purge of the clipboard*/
		do
		{
			printf(textMain[1]);
			scanf("%c", &confirm);
			while (purge = _fgetchar(), purge != '\n' && purge != EOF);
			printf("\n");
		} while (confirm != 'y' && confirm != 'n' && confirm != 'Y' && confirm != 'N');

		if (confirm == 'n' || confirm == 'N') { initGrid(playerGrid); }
	}

	system("cls");
}

/*Procedure placeBoats : places one boat on the player's grid + checks for input errors : 
input coordinates validity, size of the boat, and override with other boats*/
static void placeBoats(Tile playerGrid[][10], Boat boatGrid[], FILE *interfaceText, int boatSize, int boatId)
{
	int isInputInvalid, isBoatSizeWrong, isBoatOverriding = 1;
	char i, purge, text[3][MAX_SIZE], error[3][MAX_SIZE];
	Tile pos1, pos2;

	/*Initialising the variables used in the game for each boat : size, and state (sunk or not)*/
	boatGrid[boatId].size = boatSize;
	boatGrid[boatId].isSunk = 0;
	
	/*Reading all the interface messages from the file*/
	rewind(interfaceText);
	for (i = 0; i <= 1; i++) { fgets(text[0], MAX_SIZE, interfaceText); }
	fgets(text[1], MAX_SIZE, interfaceText);
	fgets(error[0], MAX_SIZE, interfaceText);
	fgets(error[1], MAX_SIZE, interfaceText);
	fgets(error[2], MAX_SIZE, interfaceText);
	fgets(text[2], MAX_SIZE, interfaceText);
	removeLastChar(text[1]);

	while (isBoatOverriding != 0)
	{
		isBoatSizeWrong = 1;
		while (isBoatSizeWrong != 0)
		{
			isInputInvalid = 1;
			while (isInputInvalid != 0)
			{
				/*Reading of the 2 coordinates for the boat placement + purge of the clipboard*/
				printf(text[0], boatSize);
				printf(text[1]);
				scanf("%c%c %c%c", &pos1.y, &pos1.x, &pos2.y, &pos2.x);
				while (purge = _fgetchar(), purge != '\n' && purge != EOF);
				printf("\n");
				pos1.x = pos1.x - 48;
				pos2.x = pos2.x - 48;
				pos1.y = pos1.y - 65;
				pos2.y = pos2.y - 65;

				/*If the coordinates are out of bounds, the input is declared invalid*/
				if ((0 <= pos1.y) && (pos1.y <= 9) && (0 <= pos1.x) && (pos1.x <= 9) && (0 <= pos2.y) && (pos2.y <= 9) && (0 <= pos2.x) && (pos2.x <= 9))
				{
					isInputInvalid = 0;
				}
				else
				{
					/*Error display : invalid input*/
					printf(error[0]);
					printf("\n");
				}
			}

			/*Boat size test*/
			if (((pos1.x == pos2.x) && (abs(pos2.y - pos1.y) + 1 == boatSize)) || ((pos1.y == pos2.y) && (abs(pos2.x - pos1.x) + 1 == boatSize)))
			{
				isBoatSizeWrong = 0;
			}
			else
			{
				/*Error display : wrong size of boat*/
				printf(error[1]);
				printf("\n");
			}
		}

		/*Override test and placement of the boats on the grid if it is safe. 2 different algorithms,
		depending on which coordinate is static*/
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
			/*If there is no override, display of the grid and of the registration message*/
			printf(text[2]);
			displayGrid(playerGrid, pers);
		}
		else
		{
			/*Error display : boats are overriding*/
			printf(error[2]);
			printf("\n");
		}
	}
}
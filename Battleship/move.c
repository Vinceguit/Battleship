#include <string.h>
#include "stdafx.h"

/*Function playerMove : executes the turn of a player. Asks for a target coordinate, checks if any boat is
hit or sunk, of if it missed. Displays the result of the turn on the target player's grid.
Returns if the game is over or not.*/
int playerMove(Tile gridPers[][10], Tile gridEnemy[][10], Boat boatGrid[], char playerId, FILE *interfaceText)
{
	int isInputInvalid, isAlreadyTargeted = 1, isBoatHit = 0, isBoatSunk, isOpponentDown = 1;
	char i, j, purge, text[12][MAX_SIZE], error[2][MAX_SIZE], result[8];
	Tile posTarget;

	/*Reading all the interface messages from the file*/
	rewind(interfaceText);
	for (i = 0; i <= 3; i++) { fgets(error[0], MAX_SIZE, interfaceText); }
	for (i = 4; i <= 9; i++) { fgets(text[0], MAX_SIZE, interfaceText); }
	for (i = 1; i <= 11; i++) { fgets(text[i], MAX_SIZE, interfaceText); }
	fgets(error[1], MAX_SIZE, interfaceText);
	removeLastChar(text[3]);
	removeLastChar(text[10]);
	removeLastChar(text[11]);
	strcpy(result, text[4]); // The default result of the move is "Miss !\n"

	/*Turn beginning : display of the grids*/
	printf(text[0], playerId);
	printf("\n");
	printf(text[10]);
	getchar();
	printf("\n");
	printf(text[1]);
	displayGrid(gridPers, pers);
	printf(text[2]);
	displayGrid(gridEnemy, enemy);

	while (isAlreadyTargeted != 0)
	{
		isInputInvalid = 1;
		while (isInputInvalid != 0)
		{
			/*Reading of the target coordinate + purge of the clipboard*/
			printf(text[3], playerId);
			scanf("%c%c", &posTarget.y, &posTarget.x);
			while (purge = _fgetchar(), purge != '\n' && purge != EOF);
			printf("\n");
			posTarget.x -= 48;
			posTarget.y -= 65;

			if ((0 <= posTarget.x) && (posTarget.x <= 9) && (0 <= posTarget.y) && (posTarget.y <= 9))
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

		if (gridEnemy[posTarget.x][posTarget.y].stateEnemy == 0)
		{
			isAlreadyTargeted = 0;
		}
		else
		{
			/*Error display : coordinate already targeted*/
			printf(error[1]);
			printf("\n");
		}
	}

	/*Main algorithm : searches if the target coordinate corresponds to a boat in the boat grid, for
	every boat which is not sunk. Stops if the boat is hit or if the target is missed.*/
	i = 0;
	while ((i <= 4) && (isBoatHit == 0))
	{
		if (boatGrid[i].isSunk == 0)
		{
			isBoatSunk = 1;
			for (j = 0; j <= boatGrid[i].size - 1; j++)
			{
				/*For each coordinate in the boat, checks if it is the same as the target coordinate.
				If it is, the state of this coordinate is changed.*/
				if ((posTarget.x == boatGrid[i].coord[j].x) && (posTarget.y == boatGrid[i].coord[j].y))
				{
					boatGrid[i].coord[j].state = 'X';
					gridEnemy[posTarget.x][posTarget.y].statePers = 'X';
					gridEnemy[posTarget.x][posTarget.y].stateEnemy = 'X';
					isBoatHit = 1;
				}

				/*If there is a coordinate which is not hit on the boat, it is not sunk.*/
				if (boatGrid[i].coord[j].state != 'X')
				{
					isBoatSunk = 0;
				}
			}

			/*Result display : the boat is sunk, hit or missed.*/
			if (isBoatSunk == 1)
			{
				strcpy(result, text[6]);
				boatGrid[i].isSunk = 1;
			}
			else if (isBoatHit == 1)
			{
				strcpy(result, text[5]);
			}
		}
		i++;
	}

	/*If the target is missed, a '~' is displayed on the grid to indicate where the target has missed*/
	if (isBoatHit == 0)
	{
		gridEnemy[posTarget.x][posTarget.y].statePers = '~';
		gridEnemy[posTarget.x][posTarget.y].stateEnemy = '~';
	}

	/*If there is still a boat which is not sunk on the grid, the game is not over*/
	for (i = 0; i <= 4; i++)
	{
		if (boatGrid[i].isSunk == 0) { isOpponentDown = 0; }
	}

	/*Display of the result of the move*/
	printf(result);
	printf("\n");

	/*If the opponent is down, the game ends and displays the ending message. Else, the enemy's grid
	(from an enemy state) is displayed.*/
	if (isOpponentDown == 1)
	{
		getchar();
		printf(text[7]);
		printf(text[8], playerId);
		printf("\n");
		printf(text[9], 1);
		if (playerId == 1) { displayGrid(gridPers, pers); }
		else if (playerId == 2) { displayGrid(gridEnemy, pers); }
		printf(text[9], 2);
		if (playerId == 1) { displayGrid(gridEnemy, pers); }
		else if (playerId == 2) { displayGrid(gridPers, pers); }
	}
	else 
	{
		displayGrid(gridEnemy, enemy);
		printf("\n\n");
		printf(text[11], playerId);
		getchar();
	}
	system("cls");
	return isOpponentDown;
}
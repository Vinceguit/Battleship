#include "stdafx.h"
#include "move.h"

int main(int argc, char *argv[])
{
	FILE *interfaceText = NULL;
	int langChoice = 0;

	/*Program title*/
	printf("-----------------BATTLESHIP-----------------\n\n");

	/*Language selection : opens the file corresponding to the selected language*/
	while ((langChoice != 1) && (langChoice != 2))
	{
		printf("[1]English\n[2]Francais\nChoose your language : ");
		scanf("%d", &langChoice);
	}
	if (langChoice == 1) { interfaceText = fopen("interface_en.txt", "r"); }
	else if (langChoice == 2) { interfaceText = fopen("interface_fr.txt", "r"); }
	system("cls");

	/*Main execution*/
	if (interfaceText != NULL)
	{
		int isGameOver = 0;
		Tile gridP1[10][10], gridP2[10][10];
		Boat boatsP1[5], boatsP2[5];

		/*Grid initialisation*/
		setGrid(gridP1, boatsP1, 1, interfaceText);
		setGrid(gridP2, boatsP2, 2, interfaceText);

		/*Main game*/
		firstMove(interfaceText);
		while (isGameOver == 0)
		{
			isGameOver = playerMove(gridP1, gridP2, boatsP2, 1, interfaceText);
			if (isGameOver == 0) { isGameOver = playerMove(gridP2, gridP1, boatsP1, 2, interfaceText); }
		}

		getchar();
		fclose(interfaceText);
		return 0;
	}
	else
	{
		/*Error : security if the file cannot be loaded*/
		printf("An error occured while loading interface.txt. Press Enter to exit ...");
		getchar();
		getchar();
		return 1;
	}
}
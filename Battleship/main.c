#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"

int main(int argc, char *argv[])
{
	Tile gridP1[10][10], gridP2[10][10];
	Boat boatsP1[5], boatsP2[5];

	initGrid(gridP1);
	displayGrid(gridP1, pers);
	printf("Taille d'1 grille de joueurs : %d octets\n", sizeof(gridP1));
	printf("Taille d'1 grille de bateaux : %d octets \n\n", sizeof(boatsP1));
	setGrid(gridP1, boatsP1);
	system("pause");
	return 0;
}
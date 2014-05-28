#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"

int testOverride_xStatic(Tile playerGrid[][10], Boat boatGrid[], Tile pos1, Tile pos2, int boatId)
{
	int i, j = 0;

	if (pos1.y > pos2.y) { exchange(&pos1.y, &pos2.y); }
	for (i = pos1.y; i <= pos2.y; i++)
	{
		if (playerGrid[pos1.x][i].statePers == 'O') { return 1; }
	}

	if (testOverride_xStatic == 0)
	{
		for (i = pos1.y; i <= pos2.y; i++)
		{
			playerGrid[pos1.x][i].statePers = 'O';
			boatGrid[boatId].coord[j].x = pos1.x;
			boatGrid[boatId].coord[j].y = i;
			j = j + 1;
		}
	}
}

int testOverride_yStatic(Tile playerGrid[][10], Boat boatGrid[], Tile pos1, Tile pos2, int boatId)
{
	int i, j = 0;

	if (pos1.x > pos2.x) { exchange(&pos1.x, &pos2.x); }
	for (i = pos1.x; i <= pos2.x; i++)
	{
		if (playerGrid[i][pos1.y].statePers == 'O') { return 1; }
	}

	if (testOverride_yStatic == 0)
	{
		for (i = pos1.x; i <= pos2.x; i++)
		{
			playerGrid[i][pos1.y].statePers = 'O';
			boatGrid[boatId].coord[j].x = i;
			boatGrid[boatId].coord[j].y = pos1.y;
			j = j + 1;
		}
	}
}
#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"

/*Function testOverride_xStatic : tests for the input boat IN COLUMN if there is any override of an existing boat, if not the boat is placed and registered on the boat grid. Returns the override status (0 or 1)*/
int testOverride_xStatic(Tile playerGrid[][10], Boat boatGrid[], Tile pos1, Tile pos2, int boatId)
{
	int i, j = 0, override = 0;

	/*Exchange of coordinates if necessary for the "while" loop*/
	if (pos1.y > pos2.y) { exchangeChr(&pos1.y, &pos2.y); }
	i = pos1.y;

	/*Test of the override*/
	while ((i <= pos2.y) && (override == 0))
	{
		if (playerGrid[pos1.x][i].statePers == 0) { override = 0; }
		else { override = 1; }
		i++;
	}

	/*If there is no override, placement of the boat, and registration of the boat in the boat grid*/
	if (override == 0)
	{
		for (i = pos1.y; i <= pos2.y; i++)
		{
			playerGrid[pos1.x][i].statePers = 'O';
			boatGrid[boatId].coord[j].x = pos1.x;
			boatGrid[boatId].coord[j].y = i;
			j++;
		}
	}

	return override;
}

/*Function testOverride_yStatic : Same function as x_Static, but the input boat is IN LINE. Returns the override status (0 or 1)*/
int testOverride_yStatic(Tile playerGrid[][10], Boat boatGrid[], Tile pos1, Tile pos2, int boatId)
{
	int i, j = 0, override = 0;

	if (pos1.x > pos2.x) { exchangeChr(&pos1.x, &pos2.x); }
	i = pos1.x;

	while ((i <= pos2.x) && (override == 0))
	{
		if (playerGrid[i][pos1.y].statePers == 0) { override = 0; }
		else { override = 1; }
		i++;
	}

	if (override == 0)
	{
		for (i = pos1.x; i <= pos2.x; i++)
		{
			playerGrid[i][pos1.y].statePers = 'O';
			boatGrid[boatId].coord[j].x = i;
			boatGrid[boatId].coord[j].y = pos1.y;
			j++;
		}
	}

	return override;
}
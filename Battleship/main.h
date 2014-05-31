typedef enum gridType {pers, enemy} gridType;

typedef struct Tile
{
	char x, y, statePers, stateEnemy;
} Tile;

typedef struct BoatCoord
{
	char x, y, state;
} BoatCoord;

typedef struct Boat
{
	BoatCoord coord[5];
	int size, isSunk;
} Boat;


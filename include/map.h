#define MAPSIZE 32

struct MAP_TILE {
	unsigned int height  : 2; /* height is 0-3 */
	unsigned int flooded : 1;
	unsigned int deep    : 1; /* only if flooded */
	unsigned int blocked : 1; /* mark edge of map */
	unsigned int seen    : 1;
	unsigned int visited : 1;
	char mlet;
};

struct MAP {
	unsigned int x, y, z;      /* map is chunk of larger world */
	struct MAP_TILE *tiles[MAPSIZE][MAPSIZE];
};

struct MAP *init_map_blank();

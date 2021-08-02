struct MAP_TILE {
	unsigned int height  : 2; /* height is 0-3 */
	unsigned int flooded : 1;
	unsigned int deep    : 1; /* only if flooded */
	unsigned int edge    : 1; /* mark edge of map */
};

struct MAP {
	unsigned int x, y, z;      /* map is chunk of larger world */
	struct MAP_TILE *tiles[256][256]; /* map has 256x256 tiles */
};

struct MAP *init_map_blank();

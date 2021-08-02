#include <stdlib.h>
#include "map.h"

struct MAP *init_map_blank()
{
	struct MAP *new_map;

	new_map = (struct MAP *) malloc(sizeof(struct MAP));

	new_map->x = 0;
	new_map->y = 0;
	new_map->z = 0;

	for (int i = 0; i < 256; i++) {
		new_map->tiles[0][i] = (struct MAP_TILE *) malloc(sizeof(struct MAP_TILE));
		new_map->tiles[0][i]->height = 0;
		new_map->tiles[0][i]->flooded = 0;
		new_map->tiles[0][i]->deep = 0;
		new_map->tiles[0][i]->edge = 1;

		new_map->tiles[255][i] = (struct MAP_TILE *) malloc(sizeof(struct MAP_TILE));
		new_map->tiles[255][i]->height = 0;
		new_map->tiles[255][i]->flooded = 0;
		new_map->tiles[255][i]->deep = 0;
		new_map->tiles[255][i]->edge = 1;
	}

	for (int i = 1; i < 255; i++) {
		new_map->tiles[i][0] = (struct MAP_TILE *) malloc(sizeof(struct MAP_TILE));
		new_map->tiles[i][0]->height = 0;
		new_map->tiles[i][0]->flooded = 0;
		new_map->tiles[i][0]->deep = 0;
		new_map->tiles[i][0]->edge = 1;

		new_map->tiles[i][255] = (struct MAP_TILE *) malloc(sizeof(struct MAP_TILE));
		new_map->tiles[i][255]->height = 0;
		new_map->tiles[i][255]->flooded = 0;
		new_map->tiles[i][255]->deep = 0;
		new_map->tiles[i][255]->edge = 1;
	}

	for (int i = 1; i < 255; i++) {
		for (int j = 1; j < 255; j++) {
			new_map->tiles[i][j] = (struct MAP_TILE *) malloc(sizeof(struct MAP_TILE));
		new_map->tiles[i][j]->height = 0;
		new_map->tiles[i][j]->flooded = 0;
		new_map->tiles[i][j]->deep = 0;
		new_map->tiles[i][j]->edge = 0;
		}
	}

	return new_map;
}

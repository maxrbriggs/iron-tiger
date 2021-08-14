#include <stdlib.h>
#include "map.h"

#ifndef MAPSIZE
#define MAPSIZE 256
#endif

struct MAP *init_map_blank()
{
	struct MAP *new_map;

	new_map = malloc(sizeof(struct MAP));

	new_map->x = 0;
	new_map->y = 0;
	new_map->z = 0;

	for (int i = 0; i < MAPSIZE; i++) {
		new_map->tiles[0][i] = malloc(sizeof(struct MAP_TILE));
		new_map->tiles[0][i]->height = 0;
		new_map->tiles[0][i]->flooded = 0;
		new_map->tiles[0][i]->deep = 0;
		new_map->tiles[0][i]->blocked = 1;
		new_map->tiles[0][i]->seen = 0;
		new_map->tiles[0][i]->visited = 0;
		new_map->tiles[0][i]->mlet = '#';

		new_map->tiles[MAPSIZE - 1][i] = malloc(sizeof(struct MAP_TILE));
		new_map->tiles[MAPSIZE - 1][i]->height = 0;
		new_map->tiles[MAPSIZE - 1][i]->flooded = 0;
		new_map->tiles[MAPSIZE - 1][i]->deep = 0;
		new_map->tiles[MAPSIZE - 1][i]->blocked = 1;
		new_map->tiles[MAPSIZE - 1][i]->mlet = '#';
	}

	for (int i = 1; i < MAPSIZE - 1; i++) {
		new_map->tiles[i][0] = malloc(sizeof(struct MAP_TILE));
		new_map->tiles[i][0]->height = 0;
		new_map->tiles[i][0]->flooded = 0;
		new_map->tiles[i][0]->deep = 0;
		new_map->tiles[i][0]->blocked = 1;
		new_map->tiles[i][0]->seen = 0;
		new_map->tiles[i][0]->visited = 0;
		new_map->tiles[i][0]->mlet = '#';

		new_map->tiles[i][MAPSIZE - 1] = malloc(sizeof(struct MAP_TILE));
		new_map->tiles[i][MAPSIZE - 1]->height = 0;
		new_map->tiles[i][MAPSIZE - 1]->flooded = 0;
		new_map->tiles[i][MAPSIZE - 1]->deep = 0;
		new_map->tiles[i][MAPSIZE - 1]->blocked = 1;
		new_map->tiles[i][MAPSIZE - 1]->seen = 0;
		new_map->tiles[i][MAPSIZE - 1]->visited = 0;
		new_map->tiles[i][MAPSIZE - 1]->mlet = '#';
	}

	for (int i = 1; i < MAPSIZE - 1; i++) {
		for (int j = 1; j < MAPSIZE - 1; j++) {
			new_map->tiles[i][j] = malloc(sizeof(struct MAP_TILE));
		new_map->tiles[i][j]->height = 0;
		new_map->tiles[i][j]->flooded = 0;
		new_map->tiles[i][j]->deep = 0;
		new_map->tiles[i][j]->blocked = 0;
		new_map->tiles[i][j]->seen = 0;
		new_map->tiles[i][j]->visited = 0;
		new_map->tiles[i][j]->mlet = ' ';
		}
	}

	return new_map;
}

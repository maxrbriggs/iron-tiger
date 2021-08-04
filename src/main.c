#include <stdlib.h>
#include <ncurses.h>
#include "map.h"
#include "peragent.h"
#include "peragent_list.h"
#include "agent.h"
#include "agent_actions.h"

#ifndef MAPSIZE
#define MAPSIZE 256
#endif

void read_keys(int, struct AGENT *, struct MAP *);
WINDOW *init_main_win();
void fill_map(struct MAP *, WINDOW *);

int main()
{
	WINDOW *main_win;
	int key;

	struct MAP *main_map = init_map_blank();

	extern struct PERAGENT AGENTLIST[]; /* probably not a good idea */
	struct AGENT player;

	player.data = &AGENTLIST[0];

	/* put player in middle of map */
	player.ay = MAPSIZE / 2 - 1;
	player.ax = MAPSIZE / 2 - 1;

	/* ncurses init */
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);
	noecho();
	refresh();

	/* initialize screen and map */
	main_win = init_main_win();
	fill_map(main_map, main_win);

	mvwprintw(main_win, player.ay, player.ax, "%c", player.data->alet);
	wrefresh(main_win);

	while ((key = getch()) != KEY_F(1)) {
		mvwprintw(main_win, player.ay, player.ax, "%c", main_map->tiles[player.ay][player.ax]->mlet); /* replace pc char with tile under */
		read_keys(key, &player, main_map);
		mvwprintw(main_win, player.ay, player.ax, "%c", player.data->alet);
		wrefresh(main_win);
	}
	endwin();

	for (int i = 0; i < MAPSIZE; i++){
		for (int j = 0; j < MAPSIZE; j++) {
			free(main_map->tiles[i][j]);
		}
	}

	free(main_map);


	return 0;
}

void read_keys(int keys, struct AGENT *pc, struct MAP *map)
{
	switch(keys) {
	/* momement */
	case KEY_LEFT:
		agent_move(pc, map, 0, -1);
		break;
	case 'h':
		agent_move(pc, map, 0, -1);
		break;
	case KEY_RIGHT:
		agent_move(pc, map, 0, 1);
		break;
	case 'l':
		agent_move(pc, map, 0, 1);
		break;
	case KEY_UP:
		agent_move(pc, map, -1, 0);
		break;
	case 'k':
		agent_move(pc, map, -1, 0);
		break;
	case KEY_DOWN:
		agent_move(pc, map, 1, 0);
		break;
	case 'j':
		agent_move(pc, map, 1, 0);
		break;
	case 'y':
		agent_move(pc, map, -1, -1);
		break;
	case 'u':
		agent_move(pc, map, -1, 1);
		break;
	case 'n':
		agent_move(pc, map, 1, 1);
		break;
	case 'b':
		agent_move(pc, map, 1, -1);
		break;
	}
}

WINDOW *init_main_win()
{
	int scry, scrx;
	WINDOW *new_win;

	getmaxyx(stdscr, scry, scrx);

	new_win = newwin(scry - 4, scrx - 16, 0, 0);
	wrefresh(new_win);

	return new_win;
}

void fill_map(struct MAP * map, WINDOW * win)
{
	for (int i = 0; i < MAPSIZE; i++) {
		for (int j = 0; j < MAPSIZE; j++) {
			mvwprintw(win, i, j, "%c", map->tiles[i][j]->mlet);
		}
	}
}

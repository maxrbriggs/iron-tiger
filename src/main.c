#include <stdlib.h>
#include <ncurses.h>
#include "map.h"
#include "peragent.h"
#include "peragent_list.h"
#include "agent.h"
#include "actions.h"
#include "agent_actions.h"

#ifndef MAPSIZE
#define MAPSIZE 256
#endif

struct ACTION_QUEUE_ENTRY *read_keys(int, struct AGENT *, struct MAP *);
WINDOW *init_main_win();
void fill_map(struct MAP *, WINDOW *);

int main()
{
	WINDOW *main_win;
	int key;

	struct MAP *main_map = init_map_blank(16, 16);
	struct ACTION_QUEUE *action_queue;
	struct ACTION_QUEUE_ENTRY *action;

	struct AGENT_LIST *agent_list;
	extern const struct PERAGENT PERAGENTLIST[]; /* probably not a good idea */

	struct AGENT **player;

	/* initialize action queue */
	action_queue = malloc(sizeof(struct ACTION_QUEUE));
	action_queue->head = NULL;
	action_queue->tail = NULL;

	/* initialize agent_list */
	agent_list = malloc(sizeof(struct AGENT_LIST));
	agent_list->head = NULL;
	agent_list->tail = NULL;

	add_agent(agent_list, malloc(sizeof(struct AGENT)), &PERAGENTLIST[0]);

	player = &agent_list->head->agent;

	/* put player in middle of map */
	(*player)->y = main_map->sizey / 2 - 1;
	(*player)->x = main_map->sizex / 2 - 1;

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

	mvwprintw(main_win, (*player)->y, (*player)->x, "%c",
			(*player)->data->alet);
	wrefresh(main_win);

	while ((key = getch()) != KEY_F(1)) {
		/* replace pc char with tile under */
		mvwprintw(main_win, (*player)->y, (*player)->x,
				"%c",
				main_map->tiles[(*player)->y][(*player)->x]->mlet);
		action = read_keys(key, (*player), main_map);
		enqueue_action(action, action_queue);
		resolve_actions(action_queue);
		update_agents(agent_list, action_queue);
		clear_action_queue(action_queue);
		mvwprintw(main_win, (*player)->y, (*player)->x,
				"%c", (*player)->data->alet);
		wrefresh(main_win);
	}
	endwin();

	for (int i = 0; i < main_map->sizey; i++){
		for (int j = 0; j < main_map->sizex; j++) {
			free(main_map->tiles[i][j]);
			main_map->tiles[i][j] = NULL;
		}
	}

	free(main_map);
	main_map = NULL;

	return 0;
}

struct ACTION_QUEUE_ENTRY *read_keys(int keys, struct AGENT *pc, struct MAP *map)
{
	struct ACTION_QUEUE_ENTRY *new_entry;

	switch(keys) {
	/* momement */
	case KEY_LEFT:
	case 'h':
		new_entry = agent_move(pc, map, 0, -1);
		break;
	case KEY_RIGHT:
	case 'l':
		new_entry = agent_move(pc, map, 0, 1);
		break;
	case KEY_UP:
	case 'k':
		new_entry = agent_move(pc, map, -1, 0);
		break;
	case KEY_DOWN:
	case 'j':
		new_entry = agent_move(pc, map, 1, 0);
		break;
	case 'y':
		new_entry = agent_move(pc, map, -1, -1);
		break;
	case 'u':
		new_entry = agent_move(pc, map, -1, 1);
		break;
	case 'n':
		new_entry = agent_move(pc, map, 1, 1);
		break;
	case 'b':
		new_entry = agent_move(pc, map, 1, -1);
		break;
	}

	return new_entry;
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
	for (int i = 0; i < map->sizey; i++) {
		for (int j = 0; j < map->sizex; j++) {
			mvwprintw(win, i, j, "%c", map->tiles[i][j]->mlet);
		}
	}
}

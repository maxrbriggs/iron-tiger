#include <stdlib.h>
#include <stdarg.h>
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
struct ACTION_QUEUE_ENTRY *move_random(struct AGENT *, struct MAP *);

int main()
{
	WINDOW *main_win;
	int key;

	struct MAP *main_map = init_map_blank(16, 16);
	struct ACTION_QUEUE *action_queue;
	struct ACTION_QUEUE_ENTRY *action_queue_entry;

	struct AGENT_LIST_ENTRY *agent_list_entry;
	struct AGENT_LIST *agent_list;
	extern const struct PERAGENT PERAGENTLIST[]; /* probably not a good idea */

	struct AGENT **player;
	struct AGENT **npc;

	/* initialize action queue */
	action_queue = malloc(sizeof(struct ACTION_QUEUE));
	action_queue->head = NULL;
	action_queue->tail = NULL;

	/* initialize agent_list */
	agent_list = malloc(sizeof(struct AGENT_LIST));
	agent_list->head = NULL;
	agent_list->tail = NULL;

	add_agent(agent_list, malloc(sizeof(struct AGENT)), &PERAGENTLIST[0]);
	add_agent(agent_list, malloc(sizeof(struct AGENT)), &PERAGENTLIST[1]);

	player = &agent_list->head->agent;
	npc = &agent_list->tail->agent; /* probably better to represent agent
					   list as an array */

	/* put player in middle of map */
	(*player)->y = main_map->sizey / 2 - 1;
	(*player)->x = main_map->sizex / 2 - 1;

	/* put npc in corner of map */
	(*npc)->y = 2;
	(*npc)->x = 2;

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

	/* initialize chacters to screen */
	agent_list_entry = agent_list->head;
	do {
		mvwprintw(main_win, agent_list_entry->agent->y,
				agent_list_entry->agent->x, "%c",
				agent_list_entry->agent->data->alet);
		agent_list_entry = agent_list_entry->next;
	} while (agent_list_entry);
	wrefresh(main_win);

	/** MAIN LOOP **/
	while ((key = getch()) != KEY_F(1)) {
		/* replace agent char with tile under */
		agent_list_entry = agent_list->head;
		do {
			mvwprintw(main_win, agent_list_entry->agent->y,
					agent_list_entry->agent->x, "%c",
					main_map->tiles[agent_list_entry->agent->y][agent_list_entry->agent->x]->mlet);
			agent_list_entry = agent_list_entry->next;
		} while (agent_list_entry);

		action_queue_entry = read_keys(key, (*player), main_map);
		if (action_queue_entry) {
			enqueue_action(action_queue_entry, action_queue);
			action_queue_entry = move_random((*npc), main_map);
			enqueue_action(action_queue_entry, action_queue);
			resolve_actions(action_queue);

			/* write agent chars to their map spots */
			agent_list_entry = agent_list->head;
			do {
				mvwprintw(main_win, agent_list_entry->agent->y,
						agent_list_entry->agent->x, "%c",
						agent_list_entry->agent->data->alet);
				agent_list_entry = agent_list_entry->next;
			} while (agent_list_entry);

			wrefresh(main_win); /* update window */
		}
	}
	endwin();

	/* Free all memory allocated for map tiles. Probably not
	   necessary when we're ending the program */
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
	struct ACTION_QUEUE_ENTRY *new_entry =
		malloc(sizeof(struct ACTION_QUEUE_ENTRY));

	new_entry->action_data.ptr_data = malloc(sizeof(void *) * 2);
	new_entry->action_data.int_data = malloc(sizeof(int) * 2);
	new_entry->action_data.ptr_data_length = 2;
	new_entry->action_data.int_data_length = 2;

	new_entry->action_data.ptr_data[0] = pc;
	new_entry->action_data.ptr_data[1] = map;
	new_entry->next = NULL;

	new_entry->action_fuction = NULL;

	switch(keys) {
	/* momement */
	case KEY_LEFT:
	case 'h':
		new_entry->action_fuction = agent_move;
		new_entry->action_data.int_data[0] = 0;
		new_entry->action_data.int_data[1] = -1;
		break;
	case KEY_RIGHT:
	case 'l':
		new_entry->action_fuction = agent_move;
		new_entry->action_data.int_data[0] = 0;
		new_entry->action_data.int_data[1] = 1;
		break;
	case KEY_UP:
	case 'k':
		new_entry->action_fuction = agent_move;
		new_entry->action_data.int_data[0] = -1;
		new_entry->action_data.int_data[1] = 0;
		break;
	case KEY_DOWN:
	case 'j':
		new_entry->action_fuction = agent_move;
		new_entry->action_data.int_data[0] = 1;
		new_entry->action_data.int_data[1] = 0;
		break;
	case 'y':
		new_entry->action_fuction = agent_move;
		new_entry->action_data.int_data[0] = -1;
		new_entry->action_data.int_data[1] = -1;
		break;
	case 'u':
		new_entry->action_fuction = agent_move;
		new_entry->action_data.int_data[0] = -1;
		new_entry->action_data.int_data[1] = 1;
		break;
	case 'n':
		new_entry->action_fuction = agent_move;
		new_entry->action_data.int_data[0] = 1;
		new_entry->action_data.int_data[1] = 1;
		break;
	case 'b':
		new_entry->action_fuction = agent_move;
		new_entry->action_data.int_data[0] = 1;
		new_entry->action_data.int_data[1] = -1;
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
/* prints passed map into window */
{
	for (int i = 0; i < map->sizey; i++) {
		for (int j = 0; j < map->sizex; j++) {
			mvwprintw(win, i, j, "%c", map->tiles[i][j]->mlet);
		}
	}
}

struct ACTION_QUEUE_ENTRY *move_random(struct AGENT *agent, struct MAP *map)

/* generates action queue entry to move agent to a random
   adjacent space */
{
	struct ACTION_QUEUE_ENTRY *new_entry =
		malloc(sizeof(struct ACTION_QUEUE_ENTRY));

	new_entry->action_data.ptr_data = malloc(sizeof(void *) * 2);
	new_entry->action_data.int_data = malloc(sizeof(int) * 2);
	new_entry->action_data.ptr_data_length = 2;
	new_entry->action_data.int_data_length = 2;

	new_entry->action_data.ptr_data[0] = agent;
	new_entry->action_data.ptr_data[1] = map;
	new_entry->next = NULL;

	int dy = (rand() % 3) - 1;
	int dx = (rand() % 3) - 1;

	new_entry->action_data.int_data[0] = dy;
	new_entry->action_data.int_data[1] = dx;

	new_entry->action_fuction=agent_move;

	return new_entry;
}

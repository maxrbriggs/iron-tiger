#include <stdlib.h>
#include <ncurses.h>
#include "map.h"
#include "agent.h"
#include "peragent.h"
#include "actions.h"
#include "agent_actions.h"

#ifndef MAPSIZE
#define MAPSIZE 256
#endif

/* Move an agent by dy spaces vertically and dx spaces horizontally
   Return 1 if successful, 0 if not
*/
int agent_move(struct ACTION_QUEUE_ENTRY_DATA * action_data)
{
	/* ptr_data[0] -> struct AGENT to move
	   ptr_data[1] -> struct MAP to move on
	*/

	struct AGENT *agent = action_data->ptr_data[0];
	struct MAP *map = action_data->ptr_data[1];

	/* int_data[0] -> change in y
	   int_data[1] -> change in x
	*/

	int dy = action_data->int_data[0];
	int dx = action_data->int_data[1];

	/* Maybe consider moving agent as far as it can before colliding.
	   Damage model for crashing through walls and such?
	*/

	int blocked = 0;

	/* if oob */
	if (agent->y + dy < 0
	   || agent->x + dx < 0
	   || agent->y + dy > map->sizey
	   || agent->x + dx > map->sizex) {
		blocked = 1;
	/* if blocked tile */
	} else if (map->tiles[agent->y + dy][agent->x]->blocked
	          || map->tiles[agent->y][agent->x + dx]->blocked) {
		blocked = 1;
	}

	if (!blocked) {
		agent->y += dy;
		agent->x += dx;
	}

	return 1;
}

int add_agent(struct AGENT_LIST *agent_list, struct AGENT *agent,
		const struct PERAGENT *agentdata)
{
	struct AGENT_LIST_ENTRY *entry;

	entry = malloc(sizeof(struct AGENT_LIST_ENTRY));
	entry->agent = agent;
	entry->agent->data = agentdata;

	if (!agent_list->head) {
		agent->id = 0;
		agent_list->head = entry;
		agent_list->tail = entry;
	} else {
		agent->id = agent_list->tail->agent->id + 1;
		agent_list->tail->next = entry;
		agent_list->tail = entry;
	}

	return 1;
}

int remove_agent(struct AGENT_LIST *agent_list, int id)
{
	int removed = 0;
	struct AGENT_LIST_ENTRY *prev = NULL;
	struct AGENT_LIST_ENTRY *entry = agent_list->head;

	while (!removed && entry) {
		if (entry->agent->id == id && !prev) {
			/* if found at head of agent_list */
			if (entry->agent) {
				free(entry->agent);
				entry->agent = NULL;
			}
			agent_list->head = entry->next;
			free(entry);
			entry = NULL;
			removed = 1;
		} else if (entry->agent->id == id) {
			if (entry->agent) {
				free(entry->agent);
				entry->agent = NULL;
			}
			prev->next = entry->next;
			free(entry);
			entry = NULL;
			removed = 1;
		} else {
			/* traverse list */
			prev = entry;
			entry = entry->next;
		}
	}

	if (removed) {
		return 1;
	} else {
		return 0;
	}
}

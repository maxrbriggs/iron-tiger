#include <stdlib.h>
#include <ncurses.h>
#include "map.h"
#include "agent.h"
#include "peragent.h"
#include "actions.h"
#include "agent_actions.h"

/* Move an agent by dy spaces vertically and dx spaces horizontally
   Return 1 if successful, 0 if not
*/
struct ACTION_QUEUE_ENTRY *agent_move(struct AGENT *tomove, struct MAP *map,
		int dy, int dx)
{
	/* Eventually we want some collision checking whether agent can move.
	   Maybe also consider moving agent as far as it can before colliding.

	   Damage model for crashing through walls and such?
	*/

	int blocked = 0;

	struct ACTION_QUEUE_ENTRY *new_entry;
	new_entry = malloc(sizeof(struct ACTION_QUEUE_ENTRY));

	if (tomove->y + dy < 0
	   || tomove->x + dx < 0
	   || tomove->y + dy > MAPSIZE
	   || tomove->x + dx > MAPSIZE) { /* check if oob */
		blocked = 1;
	} else if (map->tiles[tomove->y + dy][tomove->x]->blocked
	          || map->tiles[tomove->y][tomove->x + dx]->blocked) { /* if blocked tile */
		blocked = 1;
	}

	if (!blocked) {
		new_entry->new_state = malloc(sizeof(struct AGENT));
		new_entry->new_state->id = tomove->id;
		new_entry->new_state->data = tomove->data;
		new_entry->new_state->y = tomove->y;
		new_entry->new_state->x = tomove->x;
		new_entry->new_state->y += dy;
		new_entry->new_state->x += dx;
	} else {
		new_entry->new_state = tomove;
	}

	return new_entry;
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
			if (entry->agent) {
				free(entry->agent);
			}
			agent_list->head = entry->next;
			free(entry);
			removed = 1;
		} else if (entry->agent->id == id) {
			if (entry->agent) {
				free(entry->agent);
			}
			prev->next = entry->next;
			free(entry);
			removed = 1;
		} else {
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

int update_agents(struct AGENT_LIST *agent_list,
		struct ACTION_QUEUE *action_queue)
{
	struct AGENT_LIST_ENTRY *agent_entry = agent_list->head;
	struct ACTION_QUEUE_ENTRY *action_entry = action_queue->head;
	int agent_updated;

	while (action_entry) {
		agent_entry = agent_list->head;

		if (action_entry->updated) {
			agent_updated = 0;
			while (!agent_updated && agent_entry) {
				if (action_entry->new_state->id ==
				            agent_entry->agent->id) {
					free(agent_entry->agent);
					agent_entry->agent =
					        action_entry->new_state;
					agent_updated = 1;
				} else {
					agent_entry = agent_entry->next;
				}
			}
		}
		action_entry = action_entry->next;
	}

	return 1;
}


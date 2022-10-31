#include <stdlib.h>
#include "map.h"
#include "actions.h"

int enqueue_action(struct ACTION_QUEUE_ENTRY *entry,
		struct ACTION_QUEUE *action_queue)
{
	/* NULL entry means no action */
	if (!entry) {
		return 0;
	}

	if (!action_queue->head) {
		action_queue->head = entry;
		action_queue->tail = entry;
	} else {
		action_queue->tail->next = entry;
		action_queue->tail = entry;
	}

	return 1;
}

int resolve_actions(struct ACTION_QUEUE *action_queue)
{
	struct ACTION_QUEUE_ENTRY *action = action_queue->head;
	struct ACTION_QUEUE_ENTRY *action_prev = NULL;

	if (!action_queue->head) 
		return 0;
	
	action_queue->head = NULL;
	while (action) {
		if(action->action_fuction)
			action->action_fuction(&(action->action_data));

		action_prev = action;
		action = action->next;

		action_prev->action_data.ptr_data = NULL;
		action_prev->action_data.int_data = NULL;
		free(action_prev->action_data.ptr_data);
		free(action_prev->action_data.int_data);
		free(action_prev);
	}

	return 1;
}

int clear_action_queue(struct ACTION_QUEUE *action_queue)
{
	struct ACTION_QUEUE_ENTRY *entry = action_queue->head;
	struct ACTION_QUEUE_ENTRY *prev;

	while (entry) {
		prev = entry;
		entry = entry->next;
		free(prev);
		prev = NULL;
	}

	action_queue->head = NULL;
	action_queue->tail = NULL;

	return 1;
}

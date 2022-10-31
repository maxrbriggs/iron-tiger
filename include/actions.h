/* Agents want to do actions, so attempted actions are added to the action
   queue. Every turn, go through queue, and attempt to perform action.
   Report if action succeeds or fails.
*/

/* yes this is cursed */
struct ACTION_QUEUE_ENTRY_DATA {
	int ptr_data_length;
	void **ptr_data;
	int int_data_length;
	int *int_data;
};

struct ACTION_QUEUE_ENTRY {
	int (*action_fuction)(struct ACTION_QUEUE_ENTRY_DATA *);
	struct ACTION_QUEUE_ENTRY_DATA action_data;
	struct ACTION_QUEUE_ENTRY *next;
};

struct ACTION_QUEUE {
	struct ACTION_QUEUE_ENTRY *head;
	struct ACTION_QUEUE_ENTRY *tail;
};

int enqueue_action(struct ACTION_QUEUE_ENTRY *, struct ACTION_QUEUE *);
int resolve_actions(struct ACTION_QUEUE *);
int clear_action_queue(struct ACTION_QUEUE *);

/* Agents want to do actions, so attempted actions are added to the action
   queue. Every turn, go through queue, and attempt to perform action.
   Report if action succeeds or fails.
*/

struct ACTION_QUEUE_ENTRY {
	/* is it really a good idea to completely duplicate agents? */
	int updated;
	struct AGENT *new_state;
	struct ACTION_QUEUE_ENTRY *next;
};

struct ACTION_QUEUE {
	struct ACTION_QUEUE_ENTRY *head;
	struct ACTION_QUEUE_ENTRY *tail;
};

int enqueue_action(struct ACTION_QUEUE_ENTRY *, struct ACTION_QUEUE *);
int resolve_actions(struct ACTION_QUEUE *);
int clear_action_queue(struct ACTION_QUEUE *);

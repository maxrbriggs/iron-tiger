struct ACTION_QUEUE_ENTRY *agent_move(struct AGENT *, struct MAP *, int, int);
int add_agent(struct AGENT_LIST *, struct AGENT *, const struct PERAGENT *);
int remove_agent(struct AGENT_LIST *, int);
int update_agents(struct AGENT_LIST *, struct ACTION_QUEUE *);

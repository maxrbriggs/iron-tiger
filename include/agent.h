/* Definition of an instance of an agent */
struct AGENT {
	int id;
	const struct PERAGENT *data;
	int y, x;
};

struct AGENT_LIST_ENTRY {
	struct AGENT *agent;
	struct AGENT_LIST_ENTRY *next;
};

struct AGENT_LIST {
	struct AGENT_LIST_ENTRY *head;
	struct AGENT_LIST_ENTRY *tail;
};

/* Definition of categories of agent */
#define ANAME_SIZE 16

struct peragent {
	char alet;       /* symbol */
	char *akind[ANAME_SIZE];
};

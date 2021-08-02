#include <ncurses.h>
#include "map.h"
#include "agent.h"
#include "agent_actions.h"

/* Move an agent by dy spaces vertically and dx spaces horizontally
   Return 1 if successful, 0 if not
*/
int agent_move(struct agent *tomove, struct MAP *map, int dy, int dx)
{
	/* Eventually we want some collision checking whether agent can move.
	   Maybe also consider moving agent as far as it can before colliding.

	   Damage model for crashing through walls and such?
	*/

	int blocked = 0;

	/* check if out of bounds or a blocked tile */
	if (tomove->ay + dy < 0 || tomove->ax + dx < 0 || tomove->ay + dy > MAPSIZE || tomove->ax + dx > MAPSIZE) {
		blocked = 1;
	} else if (map->tiles[tomove->ay + dy][tomove->ax]->blocked || map->tiles[tomove->ay][tomove->ax + dx]->blocked) {
		blocked = 1;
	}

	if (!blocked) {
		tomove->ay += dy;
		tomove->ax += dx;
		return 1;
	} else {
		return 0;
	}
}

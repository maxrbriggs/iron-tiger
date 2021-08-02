#include <ncurses.h>

typedef struct _entity_struct {
	int y, x;
	char look;
} ENTITY;

void move_pc(int, ENTITY*);

int main()
{
	int ch;
	ENTITY player;

	player.y = 0;
	player.x = 0;
	player.look = '@';

	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);
	noecho();

	clear();
	mvprintw(player.y, player.x, "%c", player.look);

	while ((ch = getch()) != KEY_F(1)) {
		clear();
		move_pc(ch, &player);
		mvprintw(player.y, player.x, "%c", player.look);
		refresh();
	}
	endwin();

	return 0;
}

void move_pc(int ch, ENTITY *pc)
{
	int max_y, max_x;

	getmaxyx(stdscr, max_y, max_x);

	switch(ch) {
	case KEY_LEFT:
		if (pc->x > 0)
			pc->x--;
		break;
	case KEY_RIGHT:
		if (pc->x < max_x)
			pc->x++;
		break;
	case KEY_UP:
		if (pc->y > 0)
			pc->y--;
		break;
	case KEY_DOWN:
		if (pc->y < max_y)
			pc->y++;
		break;
	}
}

#include <ncurses.h>
#include "peragent.h"
#include "peragent_list.h"
#include "agent.h"

void move_pc(int, struct agent *);

int main()
{
	int ch;
	struct agent player;
	extern struct peragent agentlist[]; /* probably not a good idea */

	player.data = &agentlist[0];

	player.ay = 0;
	player.ax = 0;

	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);
	noecho();

	clear();
	mvprintw(player.ay, player.ax, "%c", player.data->alet);

	while ((ch = getch()) != KEY_F(1)) {
		clear();
		move_pc(ch, &player);
		mvprintw(player.ay, player.ax, "%c", player.data->alet);
		refresh();
	}
	endwin();

	return 0;
}

void move_pc(int ch, struct agent *pc)
{
	int max_y, max_x;

	getmaxyx(stdscr, max_y, max_x);

	switch(ch) {
	case KEY_LEFT:
		if (pc->ax > 0)
			pc->ax--;
		break;
	case 'h':
		if (pc->ax > 0)
			pc->ax--;
		break;
	case KEY_RIGHT:
		if (pc->ax < max_x)
			pc->ax++;
		break;
	case 'l':
		if (pc->ax < max_x)
			pc->ax++;
		break;
	case KEY_UP:
		if (pc->ay > 0)
			pc->ay--;
		break;
	case 'k':
		if (pc->ay > 0)
			pc->ay--;
		break;
	case KEY_DOWN:
		if (pc->ay < max_y)
			pc->ay++;
		break;
	case 'j':
		if (pc->ay < max_y)
			pc->ay++;
		break;
	}
}

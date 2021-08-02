#include <ncurses.h>
#include "peragent.h"
#include "peragent_list.h"
#include "agent.h"
#include "agent_actions.h"

void move_pc(int, struct agent *);

int main()
{
	int ch;

	extern struct peragent agentlist[]; /* probably not a good idea */
	struct agent player;

	player.data = &agentlist[0];

	player.ay = 0;
	player.ax = 0;

	/* ncurses init */
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
	switch(ch) {
	case KEY_LEFT:
		agent_move(pc, 0, -1);
		break;
	case 'h':
		agent_move(pc, 0, -1);
		break;
	case KEY_RIGHT:
		agent_move(pc, 0, 1);
		break;
	case 'l':
		agent_move(pc, 0, 1);
		break;
	case KEY_UP:
		agent_move(pc, -1, 0);
		break;
	case 'k':
		agent_move(pc, -1, 0);
		break;
	case KEY_DOWN:
		agent_move(pc, 1, 0);
		break;
	case 'j':
		agent_move(pc, 1, 0);
		break;
	}
}

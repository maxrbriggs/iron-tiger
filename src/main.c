#include <ncurses.h>
#include "peragent.h"
#include "peragent_list.h"
#include "agent.h"
#include "agent_actions.h"
#include "map.h"

void move_pc(int, struct agent *);
WINDOW *init_main_win();

int main()
{
	WINDOW *main_win;
	int ch;

	extern struct peragent agentlist[]; /* probably not a good idea */
	struct agent player;

	player.data = &agentlist[0];

	player.ay = 1;
	player.ax = 1;

	/* ncurses init */
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);
	noecho();
	refresh();

	main_win = init_main_win();


	mvwprintw(main_win, player.ay, player.ax, "%c", player.data->alet);
	wrefresh(main_win);

	while ((ch = getch()) != KEY_F(1)) {
		wclear(main_win);
		move_pc(ch, &player);
		mvwprintw(main_win, player.ay, player.ax, "%c", player.data->alet);
		wrefresh(main_win);
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

WINDOW *init_main_win()
{
	int scry, scrx;
	WINDOW *new_win;

	getmaxyx(stdscr, scry, scrx);

	new_win = newwin(scry - 16, scrx - 16, 0, 0);
	wrefresh(new_win);

	return new_win;
}

#include "shmup.h"

static void	setup_infobox_win(t_ncurses *visual);
static void	setup_world_win(t_ncurses *visual);
static void	setup_win_features(t_ncurses *visual);

void	erase_windows(t_ncurses *visual)
{
	werase(visual->world.win);
	werase(visual->infobox.win);
}

void	refresh_windows(t_ncurses *visual)
{
	box(visual->infobox.win, 0, 0); // draw border for infobox
	wrefresh(visual->world.win);
	wrefresh(visual->infobox.win);
}

Status	init_windows(t_ncurses *visual)
{
	getmaxyx(stdscr, visual->term_size.y, visual->term_size.x);
	if (terminal_too_small_loop(visual) != RES_SUCCESS)
		return (RES_USER_EXIT);
	setup_infobox_win(visual);
	setup_world_win(visual);
	if (visual->world.win == NULL || visual->infobox.win == NULL)
		return (RES_ERROR);
	setup_win_features(visual);
	return (RES_SUCCESS);
}

static void	setup_win_features(t_ncurses *visual)
{
	keypad(visual->world.win, true); // activate keyboard support in window
	nodelay(visual->world.win, true);
}

static void	setup_infobox_win(t_ncurses *visual)
{
	visual->infobox.size.y = INFOBOX_HEIGHT;
	visual->infobox.size.x = MIN_TERMINAL_WIDTH;
	visual->infobox.pos.y = visual->term_size.y - visual->infobox.size.y;
	visual->infobox.pos.x = (visual->term_size.x - visual->infobox.size.x) / 2;
	visual->infobox.win = newwin(
		visual->infobox.size.y, visual->infobox.size.x,
		visual->infobox.pos.y, visual->infobox.pos.x);
}

static void	setup_world_win(t_ncurses *visual)
{
	visual->world.size.y = MIN_TERMINAL_HEIGHT - INFOBOX_HEIGHT;
	visual->world.size.x = MIN_TERMINAL_WIDTH;
	visual->world.pos.y = (visual->term_size.y - MIN_TERMINAL_HEIGHT);
	visual->world.pos.x = (visual->term_size.x - visual->world.size.x) / 2;
	visual->world.win = newwin(
		visual->world.size.y, visual->world.size.x,
		visual->world.pos.y, visual->world.pos.x);
}

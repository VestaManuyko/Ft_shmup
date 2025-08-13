#include "shmup.h"

// resize handling for main program loop
Status	resize_loop(t_ncurses *visual)
{
	Status	res;

	getmaxyx(stdscr, visual->term_size.y, visual->term_size.x);
	erase();
	refresh();
	destroy_windows(visual);
	res = terminal_too_small_loop(visual);
	if (res != RES_SUCCESS)
		return (res);
	// Reinitialize windows with new sizes
	res = init_windows(visual);
	if (res != RES_SUCCESS)
		cleanup_ncurses(visual);
	return (res);
}

Status	terminal_too_small_loop(t_ncurses *visual)
{
	keypad(stdscr, TRUE);
	while (visual->term_size.y < MIN_TERMINAL_HEIGHT ||
		   visual->term_size.x < MIN_TERMINAL_WIDTH)
	{
		erase();
		refresh();
		// centering first line
		unsigned int x = visual->term_size.x / 2 - 18 / 2;
		unsigned int y = visual->term_size.y / 2 - 1;
		wbkgd(stdscr, COLOR_PAIR(COLOR_RED_ON_WHITE));
		wattron(stdscr, A_BOLD);
		mvprintw(y,x,"terminal too small"); // 18
		wattroff(stdscr, A_BOLD);
		// centering second line
		unsigned int len = ft_numlen(visual->term_size.x);
		len += ft_numlen(visual->term_size.y);
		len += ft_numlen(MIN_TERMINAL_WIDTH);
		len += ft_numlen(MIN_TERMINAL_HEIGHT);
		x = visual->term_size.x / 2 - (len + 17) / 2;
		y += 2;
		attron(COLOR_PAIR(COLOR_BLACK_ON_WHITE));
		mvprintw(y,x,"size (%i,%i) need (%i,%i)", // 17 + len
			visual->term_size.x, visual->term_size.y,
			MIN_TERMINAL_WIDTH, MIN_TERMINAL_HEIGHT);
		attroff(COLOR_PAIR(COLOR_BLACK_ON_WHITE));
		// option to quit
		if (getch() == ESCAPE)
			return (RES_USER_EXIT);
		getmaxyx(stdscr, visual->term_size.y, visual->term_size.x);
	}
	wbkgd(stdscr, COLOR_PAIR(COLOR_WHITE_ON_DARK_BLACK));
	refresh();
	keypad(stdscr, FALSE);
	return (RES_SUCCESS);
}

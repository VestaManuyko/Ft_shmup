#include "shmup.h"

void	destroy_windows(t_ncurses *visual)
{
	if (visual->world.win)
	{
		delwin(visual->world.win);
		visual->world.win = NULL;
	}
	if (visual->infobox.win)
	{
		delwin(visual->infobox.win);
		visual->infobox.win = NULL;
	}
}

void	cleanup_ncurses(t_ncurses *visual)
{
	keypad(visual->world.win, FALSE);
	destroy_windows(visual);
	endwin();
}

static void	init_ncurses(void)
{
    initscr();
    noecho(); // user typed input will not be displayed on screen
    cbreak(); // disables line buffering; typed characters immediately available
    curs_set(0); // hide cursor
    mousemask(0, NULL); // disable mouse events
	ESCDELAY = 25; // make ESC key more responsive
	// define_key("\x01", KEY_LEFT_CONTROL);  // Left Control
	// define_key("\x20", KEY_SPACE);          // Space
	// define_key("\x1F", KEY_RIGHT_CONTROL);  // Right Control
	// define_key("\x60", KEY_KP0);            // Keypad Zero
	// setlocale(LC_ALL, ""); // for proper character display; needs locale.h
}

Status	setup_ncurses(t_ncurses *visual)
{
	Status	res = RES_SUCCESS;
	
	init_ncurses();
	res = init_windows(visual);
	if (res != RES_SUCCESS)
		cleanup_ncurses(visual);
	return (res);
}

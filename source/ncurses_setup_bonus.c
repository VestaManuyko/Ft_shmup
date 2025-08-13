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
	wbkgd(stdscr, COLOR_PAIR(0));
	keypad(visual->world.win, FALSE);
	destroy_windows(visual);
	endwin();
}

static void init_colors(t_ncurses *v)
{
	start_color();
	init_pair(COLOR_RED_ON_BLACK, COLOR_RED, COLOR_DARK_BLACK);
	init_pair(COLOR_RED_ON_WHITE, COLOR_RED, COLOR_WHITE);
	init_pair(COLOR_BLACK_ON_WHITE, COLOR_BLACK, COLOR_WHITE);
	init_pair(COLOR_PLAYER_1, 162, COLOR_DARK_BLACK);
	init_pair(COLOR_PLAYER_2, 128, COLOR_DARK_BLACK);
	init_pair(COLOR_ENEMY_STATIONARY, 25, COLOR_DARK_BLACK);
	init_pair(COLOR_ENEMY_MOVING, COLOR_BLUE, COLOR_DARK_BLACK);
	init_pair(COLOR_ENEMY_CRAZY, 29, COLOR_DARK_BLACK);
	init_pair(COLOR_ENEMY_BOSS, 100, COLOR_DARK_BLACK);
	init_pair(COLOR_OBSTACLES, 231, COLOR_DARK_BLACK);
	init_pair(COLOR_PROJECTILE_PLAYER_1, 169, COLOR_DARK_BLACK);
	init_pair(COLOR_PROJECTILE_PLAYER_2, COLOR_MAGENTA, COLOR_DARK_BLACK);
	init_pair(COLOR_PROJECTILE_ENEMY, COLOR_CYAN, COLOR_DARK_BLACK);
	init_pair(COLOR_INFOBOX_BOX, 201, COLOR_DARK_BLACK);
	init_pair(COLOR_INFOBOX_TEXT, 225, COLOR_DARK_BLACK);
	init_pair(COLOR_WHITE_ON_DARK_BLACK, COLOR_WHITE, COLOR_DARK_BLACK);
	init_pair(COLOR_MUSHROOM, COLOR_GREEN, COLOR_DARK_BLACK);
	v->colored = true;
}

static void	init_ncurses(t_ncurses *v)
{
    initscr();
    noecho(); // user typed input will not be displayed on screen
    cbreak(); // disables line buffering; typed characters immediately available
    curs_set(0); // hide cursor
    mousemask(0, NULL); // disable mouse events
	ESCDELAY = 25; // make ESC key more responsive
	if (has_colors())
		init_colors(v);
	// define_key("\x01", KEY_LEFT_CONTROL);  // Left Control
	// define_key("\x20", KEY_SPACE);          // Space
	// define_key("\x1F", KEY_RIGHT_CONTROL);  // Right Control
	// define_key("\x60", KEY_KP0);            // Keypad Zero
	// setlocale(LC_ALL, ""); // for proper character display; needs locale.h
}

Status	setup_ncurses(t_ncurses *visual)
{
	Status	res = RES_SUCCESS;
	
	init_ncurses(visual);
	res = init_windows(visual);
	if (res != RES_SUCCESS)
		cleanup_ncurses(visual);
	return (res);
}

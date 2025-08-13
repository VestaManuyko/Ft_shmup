#include "shmup.h"

void	draw_info(t_world *world, t_ncurses *visual)
{
	//--------------------------------------------------------------------------
	//|   P2 1234567     P2 lives       TIME       lives P1     1234567 P1   |
	//--------------------------------------------------------------------------
	wattron(visual->infobox.win, COLOR_PAIR(COLOR_INFOBOX_TEXT));
	// fps counter
	mvwprintw(visual->infobox.win, 1, 2, "FPS %u", world->time.fps_curr);
	// [P2] section
	if (!world->player_2.active)
	{
		wattron(visual->infobox.win, A_BLINK);
		mvwprintw(visual->infobox.win, 1, 15,
			"[P2] press W/A/S/D to start [P2]");
		wattroff(visual->infobox.win, A_BLINK);
	}
	else
	{
		wattron(visual->infobox.win, COLOR_PAIR(COLOR_PLAYER_2) | A_BOLD);
		mvwaddch(visual->infobox.win, 1, 18, CH_PLAYER_2);
		wattroff(visual->infobox.win, A_BOLD);
		wattron(visual->infobox.win, COLOR_PAIR(COLOR_INFOBOX_TEXT));
		mvwprintw(visual->infobox.win, 1, 20 ,
			"[P2]  lives %3i   score %u",
			world->player_2.lives, world->player_2.score);
	}
	// time ellapsed since start
	mvwprintw(visual->infobox.win, 1, visual->infobox.size.x / 2 - 2,
		 "%02i:%02i", world->time.runtime / 60, world->time.runtime % 60);
	// optional: time remaining
	// [P1] section
	wattron(visual->infobox.win, COLOR_PAIR(COLOR_PLAYER_1) | A_BOLD);
	mvwaddch(visual->infobox.win, 1, visual->infobox.size.x - 49, CH_PLAYER_1);
	wattroff(visual->infobox.win, A_BOLD);
	wattron(visual->infobox.win, COLOR_PAIR(COLOR_INFOBOX_TEXT));
	mvwprintw(visual->infobox.win, 1, visual->infobox.size.x - 47,
		"[P1]  lives %3i    score %u",
		world->player_1.lives, world->player_1.score);
	// just some text
	mvwprintw(visual->infobox.win, 1, visual->infobox.size.x - 7,
		"shmup");
	wattroff(visual->infobox.win, COLOR_PAIR(COLOR_WHITE_ON_DARK_BLACK));
}

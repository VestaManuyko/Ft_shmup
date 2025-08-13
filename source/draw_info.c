#include "shmup.h"
#include <stdio.h> // for dprintf
void	draw_info(t_world *world, t_ncurses *visual)
{
	//--------------------------------------------------------------------------
	//| FPS 60    [P1]  lives 100    score 1234              MM:SS     01:23  |
	//--------------------------------------------------------------------------
	// fps counter (usually 6 char long; + 2 for offset = 8 total)
	mvwprintw(visual->infobox.win, 1, 2, "FPS %u", world->time.fps_curr);
	// [P1] section
	// TODO add color
	mvwprintw(visual->infobox.win, 1, 14, "lives");
	for (int i = 1; i <= world->player_1.lives; i++)
	{
		mvwaddch(visual->infobox.win, 1, 19 + i, '|');
	}
	mvwprintw(visual->infobox.win, 1, 37, "score %u", world->player_1.score);
	// optional: time remaining
	// time ellapsed since start
	mvwprintw(visual->infobox.win, 1, visual->infobox.size.x - 7,
		 "%02i:%02i", world->time.runtime / 60, world->time.runtime % 60);
}

#include "shmup.h"

void	ask_for_restart(t_world *world, t_ncurses *visual)
{
	int ch;

	if (world->status != RES_GAME_OVER)
		return ;
	usleep(150000); // wait a bit before showing game over message
	while (true)
	{
		werase(visual->world.win);
		mvwprintw(visual->world.win, visual->world.size.y / 2,
			visual->world.size.x / 2 - 16, "Game Over! Press ENTER to restart");
		ch = wgetch(visual->world.win);
		if (ch == '\n' || ch == '\r')
			break ;
		else if (ch == ESCAPE)
		{
			world->status = RES_USER_EXIT;
			break ;
		}
		else if (ch == KEY_RESIZE)
		{
			world->status = resize_loop(visual);
			if (world->status != RES_SUCCESS)
				break ;
			box(visual->infobox.win, 0, 0);
			draw_info(world, visual);
			wrefresh(visual->infobox.win);
		}
		wrefresh(visual->world.win);
	}
	if (world->status != RES_USER_EXIT && world->status != RES_ERROR)
	{
		ft_bzero(world, sizeof(t_world));
		cleanup_ncurses(visual);
	}
}

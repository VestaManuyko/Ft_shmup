#include "shmup.h"

void	draw_game(t_world *world, t_ncurses *visual)
{
	erase_windows(visual);
	draw_entities(world, visual);
	draw_info(world, visual);
	refresh_windows(visual);
}

void	draw_entities(t_world *world, t_ncurses *visual)
{
	for (int y = 0; y < MAX_GRID_HEIGHT; y++)
	{
		for (int x = 0; x < MAX_GRID_WIDTH; x++)		
		{
			if (world->grid[x][y].entity != ENT_NONE)
				world->draw[world->grid[x][y].entity](visual, x, y);
		}
	}
}

void	draw_player(t_ncurses *visual, int x, int y)
{
	// TODO attributes for player
	mvwaddch(visual->world.win, y, x, CH_PLAYER_1);
}

void	draw_enemy(t_ncurses *visual, int x, int y)
{
	// TODO attributes for ...
	mvwaddch(visual->world.win, y, x, CH_ENEMY_STATIONARY);
}

void	draw_obstacle_1(t_ncurses *visual, int x, int y)
{
	mvwaddch(visual->world.win, y, x, CH_OBSTACLE_1);
}

void	draw_projectile_player(t_ncurses *visual, int x, int y)
{
	mvwaddch(visual->world.win, y, x, CH_PROJECTILE_PLAYER_1);
}

void	draw_projectile_enemy(t_ncurses *visual, int x, int y)
{
	mvwaddch(visual->world.win, y, x, CH_PROJECTILE_ENEMY);
}

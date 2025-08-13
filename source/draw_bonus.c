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
	chtype ch = CH_PLAYER_1
		| COLOR_PAIR(COLOR_PLAYER_1)
		| A_BOLD;
	mvwaddch(visual->world.win, y, x, ch);
}

void	draw_player_2(t_ncurses *visual, int x, int y)
{
	chtype ch = CH_PLAYER_2
		| COLOR_PAIR(COLOR_PLAYER_2)
		| A_BOLD;
	mvwaddch(visual->world.win, y, x, ch);
}

void	draw_enemy(t_ncurses *visual, int x, int y)
{
	chtype ch = CH_ENEMY_STATIONARY
		| COLOR_PAIR(COLOR_ENEMY_STATIONARY)
		| A_BOLD;
	mvwaddch(visual->world.win, y, x, ch);
}
void	draw_obstacle_1(t_ncurses *visual, int x, int y)
{
	chtype ch = CH_OBSTACLE_1
		| COLOR_PAIR(COLOR_OBSTACLES)
		| A_BOLD;
	mvwaddch(visual->world.win, y, x, ch);
}
void	draw_obstacle_2(t_ncurses *visual, int x, int y)
{
	chtype ch = CH_OBSTACLE_2
		| COLOR_PAIR(COLOR_OBSTACLES)
		| A_BOLD;
	mvwaddch(visual->world.win, y, x, ch);
}
void	draw_obstacle_3(t_ncurses *visual, int x, int y)
{
	chtype ch = CH_OBSTACLE_3
		| COLOR_PAIR(COLOR_OBSTACLES)
		| A_BOLD;
	mvwaddch(visual->world.win, y, x, ch);
}
void	draw_mushroom(t_ncurses *visual, int x, int y)
{
	chtype ch = CH_MUSHROOM
		| COLOR_PAIR(COLOR_MUSHROOM)
		| A_BOLD;
	mvwaddch(visual->world.win, y, x, ch);
}
void	draw_projectile_player(t_ncurses *visual, int x, int y)
{
	chtype ch = CH_PROJECTILE_PLAYER_1
		| COLOR_PAIR(COLOR_PROJECTILE_PLAYER_1)
		| A_BOLD;
	mvwaddch(visual->world.win, y, x, ch);
}

void	draw_projectile_player_2(t_ncurses *visual, int x, int y)
{
	chtype ch = CH_PROJECTILE_PLAYER_2
		| COLOR_PAIR(COLOR_PROJECTILE_PLAYER_2)
		| A_BOLD;
	mvwaddch(visual->world.win, y, x, ch);
}
void	draw_projectile_enemy(t_ncurses *visual, int x, int y)
{
	chtype ch = CH_PROJECTILE_ENEMY
		| COLOR_PAIR(COLOR_PROJECTILE_ENEMY)
		| A_BOLD;
	mvwaddch(visual->world.win, y, x, ch);
}

#include "shmup.h"

void	handle_input(int ch, t_world *world, t_ncurses *visual)
{
	if (ch == ESCAPE)
	{
		world->status = RES_USER_EXIT;
		cleanup_ncurses(visual);
		exit(0);
	}
	else if (ch == KEY_RESIZE)
		world->status = resize_loop(visual);
	if (!world->player_1.dead)
	{
		if (ch == KEY_LEFT || ch == KEY_RIGHT || ch == KEY_UP || ch == KEY_DOWN)
			move_player_1(world, ch);
		else if (ch == '0' || ch == '.')
			spawn_projectile_player_1(world, &world->player_1);
	}
	if (!world->player_2.active && (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd'))
		spawn_player_2(world);
	if (!world->player_2.dead)
	{
		if (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd')
			move_player_2(world, ch);
		else if (ch == ' ')
			spawn_projectile_player_2(world, &world->player_2);
	}
}

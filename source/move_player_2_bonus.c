#include "shmup.h"

void	move_player_2(t_world *world, int ch)
{
	unsigned int old_x = world->player_2.pos.x;
	unsigned int old_y = world->player_2.pos.y;

	set_new_player_coord(&world->player_2, ch, 'a', 'w', 'd', 's');
	if (world->player_2.pos.x == old_x && world->player_2.pos.y == old_y)
		return ;
	if (world->grid[world->player_2.pos.x][world->player_2.pos.y].entity == ENT_PLAYER_1)
	{
		world->player_2.pos.x = old_x;
		world->player_2.pos.y = old_y;
		return ;
	}
	collision(world, world->player_2.pos.x, world->player_2.pos.y, ENT_PLAYER_2);
	if (world->player_2.dead) // reset coord for check_game_over
	{
		world->player_2.pos.x = old_x;
		world->player_2.pos.y = old_y;
	}
	world->grid[old_x][old_y].entity = ENT_NONE;
	world->grid[world->player_2.pos.x][world->player_2.pos.y].entity = ENT_PLAYER_2;
}

#include "shmup.h"

void	move_player_1(t_world *world, int ch)
{
	unsigned int old_x = world->player_1.pos.x;
	unsigned int old_y = world->player_1.pos.y;
	
	set_new_player_coord(&world->player_1, ch,
		KEY_LEFT, KEY_UP, KEY_RIGHT, KEY_DOWN);
	if (world->player_1.pos.x == old_x && world->player_1.pos.y == old_y)
		return ;
	if (world->grid[world->player_1.pos.x][world->player_1.pos.y].entity == ENT_PLAYER_2)
	{
		world->player_1.pos.x = old_x;
		world->player_1.pos.y = old_y;
		return ;
	}
	collision(world, world->player_1.pos.x, world->player_1.pos.y, ENT_PLAYER_1);
	if (world->player_1.dead) // reset coord for check_game_over
	{
		world->player_1.pos.x = old_x;
		world->player_1.pos.y = old_y;
	}
	world->grid[old_x][old_y].entity = ENT_NONE;
	world->grid[world->player_1.pos.x][world->player_1.pos.y].entity = ENT_PLAYER_1;
}

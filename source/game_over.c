#include "shmup.h"

void	check_game_over(t_world *world)
{
	if (world->player_1.dead)
	{
		if  (world->grid[world->player_1.pos.x][world->player_1.pos.y].entity == ENT_PLAYER_1)
		{
			world->grid[world->player_1.pos.x][world->player_1.pos.y].entity = ENT_NONE;
			world->player_1.lives = 0;
		}
		if (!world->player_2.active)
			world->status = RES_GAME_OVER;
	}
	if (world->player_2.active)
	{
		if (world->player_2.dead)
		{
			if (world->grid[world->player_2.pos.x][world->player_2.pos.y].entity == ENT_PLAYER_2)
			{
				world->grid[world->player_2.pos.x][world->player_2.pos.y].entity = ENT_NONE;
				world->player_2.lives = 0;
			}
			if (world->player_1.dead)
				world->status = RES_GAME_OVER;
		}
	}
}

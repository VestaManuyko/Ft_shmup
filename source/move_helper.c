#include "shmup.h"

// moves entities vertically down
void	generic_move_down(t_world *world, int x, int y)
{
	// FIXME need collision check
	if (y < MAX_GRID_HEIGHT - 1
		&& !collision(world, x, y + 1, world->grid[x][y].entity))
	{
		world->grid[x][y + 1].entity = world->grid[x][y].entity;
		world->grid[x][y + 1].last_frame = world->time.frame_count;
		world->grid[x][y + 1].health = world->grid[x][y].health;
	}
	world->grid[x][y].last_frame = 0;
	world->grid[x][y].health = 0;
	world->grid[x][y].entity = ENT_NONE;
}

// moves entities vertically up
void	generic_move_up(t_world *world, int x, int y)
{
	//FIXME need collision check
	if (y > 0 && !collision(world, x, y - 1, world->grid[x][y].entity))
	{
		world->grid[x][y - 1].entity = world->grid[x][y].entity;
		world->grid[x][y - 1].last_frame = world->time.frame_count;
		world->grid[x][y - 1].health = world->grid[x][y].health;
	}
	world->grid[x][y].last_frame = 0;
	world->grid[x][y].health = 0;
	world->grid[x][y].entity = ENT_NONE;
}

// updates player coordinates
void	set_new_player_coord(t_player *player, int ch,
	int left, int up, int right, int down)
{
	if (ch == left)
	{
		if (player->pos.x != 0)
			player->pos.x -= 1;
	}
	else if (ch == up)
	{
		if (player->pos.y != 0)
			player->pos.y -= 1;
	}
	else if (ch == right)
	{
		if (player->pos.x != MAX_GRID_WIDTH - 1)
			player->pos.x += 1;
	}
	else if (ch == down)
	{
		if (player->pos.y != MAX_GRID_HEIGHT - 1)
			player->pos.y += 1;
	}
}

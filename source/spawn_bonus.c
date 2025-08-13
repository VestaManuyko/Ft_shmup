#include "shmup.h"

static void	spawn_enemy(t_world *world)
{
	unsigned int x;
	unsigned int y;

	x = rand() % MAX_GRID_WIDTH;
	y = 0;
	world->grid[x][y].entity = ENT_ENEMY_STATIONARY;
	world->grid[x][y].last_frame = world->time.frame_count;
}

static void	spawn_obstacle(t_world *world)
{
	unsigned int x;
	unsigned int y;
	unsigned int rnd = rand() % 30;

	x = rand() % MAX_GRID_WIDTH;
	y = 0;
	if (rnd > 25)
	{
		world->grid[x][y].entity = ENT_OBSTACLE_3;
		world->grid[x][y].health = 100;
	}
	else if (rnd < 25 && rnd > 15)
	{
		world->grid[x][y].entity = ENT_OBSTACLE_2;
		world->grid[x][y].health = 2;
	}
	else
		world->grid[x][y].entity = ENT_OBSTACLE_1;
	world->grid[x][y].last_frame = world->time.frame_count;
}

static void    spawn_mushroom(t_world *world)
{
    unsigned int x;
	unsigned int y;

	x = rand() % MAX_GRID_WIDTH;
	y = 0;
	world->grid[x][y].entity = ENT_MUSHROOM;
	world->grid[x][y].last_frame = world->time.frame_count;
}

void	spawn_entities(t_world *world)
{
	static unsigned int	last_spawn;
	unsigned int p = rand() % 10;

	if (world->time.frame_count - last_spawn >= SPAWN_DELAY)
	{
        if (p < 2)
            spawn_mushroom(world);
		if (p > 5)
			spawn_enemy(world);
		if (p < 5)
			spawn_obstacle(world);
		last_spawn = world->time.frame_count;
	}
}

void	spawn_boss_wave(t_world *world)
{
	for (int y = 0; y < 2; y++)
	{
		for(int x = 0; x < MAX_GRID_WIDTH; x++)
		{
			world->grid[x][y].entity = ENT_OBSTACLE_2;
			world->grid[x][y].health = 2;
			world->grid[x][y].last_frame = world->time.frame_count;
		}
	}
}
void	spawn_wave(t_world *world)
{
	for (int y = 0; y < 1 ; y++)
	{
		for(int x = 0; x < MAX_GRID_WIDTH; x++)
		{
			world->grid[x][y].entity = ENT_OBSTACLE_1;
			world->grid[x][y].last_frame = world->time.frame_count;
		}
	}
}

void	spawn_projectile_player_1(t_world *world, t_player *player)
{
	if (player->pos.y == 0 ||
		world->grid[player->pos.x][player->pos.y - 1].entity != ENT_NONE)
	{
		return ;
	}
	world->grid[player->pos.x][player->pos.y - 1].entity = ENT_PROJECTILE_PLAYER_1;
	world->grid[player->pos.x][player->pos.y - 1].last_frame = world->time.frame_count;
}

void	spawn_projectile_player_2(t_world *world, t_player *player)
{
	if (player->pos.y == 0 ||
		world->grid[player->pos.x][player->pos.y - 1].entity != ENT_NONE)
	{
		return ;
	}
	world->grid[player->pos.x][player->pos.y - 1].entity = ENT_PROJECTILE_PLAYER_2;
	world->grid[player->pos.x][player->pos.y - 1].last_frame = world->time.frame_count;
}

void	spawn_projectile_enemy(t_world *world)
{
	int new_y;
	int count = 0;
	int rnd = rand() % 10;

	for (int y = 0; y < MAX_GRID_HEIGHT -1; y++)
	{
		for (int x = 0; x < MAX_GRID_WIDTH; x++)
		{
			if (world->grid[x][y].entity == ENT_ENEMY_STATIONARY)
			{
				count++;
				new_y = y;
				while (new_y < MAX_GRID_HEIGHT -1)
				{
					new_y++;
					if (world->grid[x][new_y].entity == ENT_ENEMY_STATIONARY)
						break ;
				}
				if (new_y == MAX_GRID_HEIGHT -1)
				{
					if (y + 1 != MAX_GRID_HEIGHT -1 && count == rnd)
					{
						world->grid[x][y + 1].entity = ENT_PROJECTILE_ENEMY;
					 	world->grid[x][y + 1].last_frame = world->grid[x][y].last_frame;
					}
				}
			}
		}
	}
}

void	spawn_player_2(t_world *world)
{
	int x = 0;
	for (int i = 0; i < MAX_GRID_WIDTH; i++)
	{
		x = rand() % MAX_GRID_WIDTH;
		if (world->grid[x][MAX_GRID_HEIGHT - 1].entity == ENT_NONE)
		{
			world->grid[x][MAX_GRID_HEIGHT - 1].entity = ENT_PLAYER_2;
			world->player_2.active = true;
			break ;
		}
	}
	if (!world->player_2.active)
	{
		x = world->player_1.pos.x;
		if (x == 0)
			x = MAX_GRID_WIDTH - 1;
		else if (x == MAX_GRID_WIDTH - 1)
			x = 0;
		world->grid[x][MAX_GRID_HEIGHT - 1].entity = ENT_PLAYER_2;
		world->player_2.active = true;
	}
	world->player_2.pos.x = x;
	world->player_2.pos.y = MAX_GRID_HEIGHT - 1;
	world->player_2.lives = LIVES_START;
}

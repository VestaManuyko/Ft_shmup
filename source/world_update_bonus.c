#include "shmup.h"

static void	move_nonplayer_entities(t_world *world)
{
	unsigned int	delta;
	Entities	entity_type;

	for (int y = MAX_GRID_HEIGHT - 1; y >= 0; y--)
	{
		for (int x = 0; x < MAX_GRID_WIDTH; x++)
		{
			entity_type = world->grid[x][y].entity;
			if (entity_type == ENT_NONE
				|| entity_type == ENT_PLAYER_1 || entity_type == ENT_PLAYER_2)
			{
				continue; // skip empty cells and player
			}
			delta = world->time.frame_count - world->grid[x][y].last_frame;
			if (delta < world->entity[entity_type].frame_delay)
				continue; // skip when not enough frames have passed
			world->entity[entity_type].move_func(world, x, y);
		}
	}
}

static void enemy_shooting(t_world *world)
{
	static unsigned int last_shoot;

	if (world->time.frame_count - last_shoot >= SHOOT_DELAY)
	{
		spawn_projectile_enemy(world);
		last_shoot = world->time.frame_count;
	}
}
static void enemy_waves(t_world *world)
{
	static unsigned int last_wave;
	static int count;
	unsigned int p = rand() % 10;

	if (world->time.frame_count - last_wave >= WAVE_DELAY)
	{
		if (p > 3)
		{
			count++;
			spawn_wave(world);
		}	
		last_wave = world->time.frame_count;
	}
	if (count == 3)
	{
		count = 0;
		spawn_boss_wave(world);
		last_wave = world->time.frame_count;
	}
}
void	update_world(t_world *world)
{
	move_nonplayer_entities(world);
	spawn_entities(world);
	enemy_shooting(world);
	enemy_waves(world);
}

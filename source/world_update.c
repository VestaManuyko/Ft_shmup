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
void	update_world(t_world *world)
{
	move_nonplayer_entities(world);
	spawn_entities(world);
	enemy_shooting(world);
	// TODO spawn new entities
	// spawn_mushroom(world); // bonus part
}

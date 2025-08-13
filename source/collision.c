#include "shmup.h"

static void	collision_w_sth(t_world *world, int x, int y);
static void	collision_w_player(t_world *world, int x, int y);
static bool	collision_w_player_projectile(t_world *world, int x, int y, Entities moving_one);
static bool	collision_detected(t_world *world, int x, int y, Entities moving_one);
static void	collision_player_w_mushroom(t_world *world, Entities moving_one);
static bool	collision_mushroom_w_player(t_world *world, int x, int y);


// takes TARGET x & y and the entity type that is moving
bool	collision(t_world *world, int x, int y, Entities moving_one)
{
	if (world->grid[x][y].entity == ENT_NONE)
		return (false);
	else if (moving_one == ENT_PLAYER_1 || moving_one == ENT_PLAYER_2)
	{
		// target space is occupied by anything other than player_2
		if (world->grid[x][y].entity == ENT_MUSHROOM)
		{
			collision_player_w_mushroom(world, moving_one);
		}
		else if (moving_one == ENT_PLAYER_1)
			player_lives_update(&world->player_1);
		else if (moving_one == ENT_PLAYER_2)
			player_lives_update(&world->player_2);
		return (true);
	}	
	else
		return (collision_detected(world, x, y, moving_one));
}

// decides what to do on a collision
static bool	collision_detected(t_world *world, int x, int y, Entities moving_one)
{
	// PART 1 --- PROJECTILEs collide INTO something
	if (moving_one == ENT_PROJECTILE_PLAYER_1)
		check_destruction(&world->player_1, &world->grid[x][y],
			world->score_table[world->grid[x][y].entity]);
	else if (moving_one == ENT_PROJECTILE_PLAYER_2)
		check_destruction(&world->player_2, &world->grid[x][y],
			world->score_table[world->grid[x][y].entity]);
	else if (moving_one == ENT_PROJECTILE_ENEMY)
	{
		if (world->grid[x][y].entity == ENT_PLAYER_1
			|| world->grid[x][y].entity == ENT_PLAYER_2)
		{
			collision_w_player(world, x, y);
		}
		else
			collision_w_sth(world, x, y);
	}
	// PART 2 --- MUSHROOM collides with PLAYER
	else if (moving_one == ENT_MUSHROOM)
	{
		return (collision_mushroom_w_player(world, x, y));
	}
	// PART 3 --- SOMETHING ELSE collides with PLAYER or PLAYER PROJECTILE
	else if (moving_one != ENT_PLAYER_1 && moving_one != ENT_PLAYER_2)
	{
		if (world->grid[x][y].entity == ENT_PLAYER_1
			|| world->grid[x][y].entity == ENT_PLAYER_2)
		{
			collision_w_player(world, x, y);
		}
		else if (world->grid[x][y].entity == ENT_PROJECTILE_PLAYER_1
			|| world->grid[x][y].entity == ENT_PROJECTILE_PLAYER_2)
		{
			return (collision_w_player_projectile(world, x, y, moving_one));
		}
	}
	return (true);
}

static void	collision_player_w_mushroom(t_world *world, Entities moving_one)
{
	if (moving_one == ENT_PLAYER_1)
		mushroom_update_player(&world->player_1);
	else if (moving_one == ENT_PLAYER_2)
		mushroom_update_player(&world->player_2);
}

static bool	collision_mushroom_w_player(t_world *world, int x, int y)
{
	if (world->grid[x][y].entity == ENT_PLAYER_1)
	{
		mushroom_update_player(&world->player_1);
		return (true);
	}
	if (world->grid[x][y].entity == ENT_PLAYER_2)
	{
		mushroom_update_player(&world->player_2);
		return (true);
	}
	return (false); // don't destroy mushroom when it hits anything else
}

// PART 3a --- SOMETHING collides with PLAYER
static void	collision_w_player(t_world *world, int x, int y)
{
	if (world->grid[x][y].entity == ENT_PLAYER_1)
		player_lives_update(&world->player_1);
	else if (world->grid[x][y].entity == ENT_PLAYER_2)
		player_lives_update(&world->player_2);
}
// PART 3b --- SOMETHING colllides with PLAYER PROJECTILE
static bool	collision_w_player_projectile(t_world *world, int x, int y, Entities moving_one)
{
	if (world->grid[x][y].entity == ENT_PROJECTILE_PLAYER_1)
	{
		return (check_destruction(&world->player_1, &world->grid[x][y - 1], world->score_table[moving_one]));
		// score(&world->player_1, &world->grid[x][y].entity, world->score_table[moving_one]);
	}
	else if (world->grid[x][y].entity == ENT_PROJECTILE_PLAYER_2)
	{
		return (check_destruction(&world->player_2, &world->grid[x][y - 1], world->score_table[moving_one]));
		// score(&world->player_2, &world->grid[x][y].entity, world->score_table[moving_one]);
	}
	return (false);
}


static void	collision_w_sth(t_world *world, int x, int y)
{
	if (world->grid[x][y].health)
	{
		world->grid[x][y].health--;
		if (world->grid[x][y].health <= 0)
		{
			world->grid[x][y].entity = ENT_NONE; // remove entity from grid
			world->grid[x][y].health = 0; // reset health
		}
	}
	else
	{
		world->grid[x][y].entity = ENT_NONE; // remove entity from grid
	}
}

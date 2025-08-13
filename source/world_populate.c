#include "shmup.h"

// will be responsible for INITIAL spawning
void	populate(t_world *world, t_ncurses *visual)
{
	unsigned int x;
	unsigned int y;
	//store the start pos of player 1
	world->player_1.pos.x = MAX_GRID_WIDTH / 2;
	world->player_1.pos.y = visual->world.size.y - 1;
	// spawn player 1
	world->grid[MAX_GRID_WIDTH / 2][visual->world.size.y - 1].entity = ENT_PLAYER_1;
	world->player_1.lives = LIVES_START;
	// spawn enemies (only stationary so far)
	for (int i = 0; i < AMOUNT_OF_ENEMIES; i++)
	{
		x = rand() % MAX_GRID_WIDTH;
		y = rand() % (MAX_GRID_HEIGHT - SAFE_SPACE);
		world->grid[x][y].entity = ENT_ENEMY_STATIONARY;
	}
	// spawn obstacles
	for (int i = 0; i < AMOUNT_OF_OBSTACLES; i++)
	{
		x = rand() % MAX_GRID_WIDTH;
		y = rand() % (MAX_GRID_HEIGHT - SAFE_SPACE);
		world->grid[x][y].entity = ENT_OBSTACLE_1;
	}
	draw_entities(world, visual);
	refresh_windows(visual);
}

#include "shmup.h"

void	init_scores(t_world *world)
{
	world->score_table[ENT_ENEMY_STATIONARY] = SCORE_ENEMY_STATIONARY;
	world->score_table[ENT_ENEMY_MOVING] = SCORE_ENEMY_MOVING;
	world->score_table[ENT_ENEMY_CRAZY] = SCORE_ENEMY_CRAZY;
	world->score_table[ENT_BOSS] = SCORE_BOSS;
	world->score_table[ENT_MUSHROOM] = SCORE_MUSHROOM;
	world->score_table[ENT_OBSTACLE_1] = SCORE_OBSTACLE_1;
	world->score_table[ENT_OBSTACLE_2] = SCORE_OBSTACLE_2;
	world->score_table[ENT_OBSTACLE_3] = SCORE_OBSTACLE_3;
}

void	init_draw_pointers(t_world *world)
{
	world->draw[ENT_PLAYER_1] = draw_player;
	world->draw[ENT_PLAYER_2] = draw_player_2;
	world->draw[ENT_ENEMY_STATIONARY] = draw_enemy;
	world->draw[ENT_OBSTACLE_1] = draw_obstacle_1;
	world->draw[ENT_PROJECTILE_PLAYER_1] = draw_projectile_player;
	world->draw[ENT_PROJECTILE_PLAYER_2] = draw_projectile_player_2;
	world->draw[ENT_PROJECTILE_ENEMY] = draw_projectile_enemy;
	world->draw[ENT_MUSHROOM] = draw_mushroom;
	world->draw[ENT_OBSTACLE_2] = draw_obstacle_2;
	world->draw[ENT_OBSTACLE_3] = draw_obstacle_3;
}

void	init_move_pointers(t_world *world)
{
	world->entity[ENT_ENEMY_STATIONARY].frame_delay = FRAME_DELAY_NONMOVING;
	world->entity[ENT_OBSTACLE_1].frame_delay = FRAME_DELAY_NONMOVING;
	world->entity[ENT_OBSTACLE_2].frame_delay = FRAME_DELAY_NONMOVING;
	world->entity[ENT_OBSTACLE_3].frame_delay = FRAME_DELAY_NONMOVING;
	world->entity[ENT_MUSHROOM].frame_delay = FRAME_DELAY_NONMOVING;
	world->entity[ENT_PROJECTILE_PLAYER_1].frame_delay = FRAME_DELAY_POJECTILE_PLAYER;
	world->entity[ENT_PROJECTILE_PLAYER_2].frame_delay = FRAME_DELAY_POJECTILE_PLAYER;
	world->entity[ENT_PROJECTILE_ENEMY].frame_delay = FRAME_DELAY_PROJECTILE_ENEMY;
	world->entity[ENT_ENEMY_STATIONARY].move_func = generic_move_down;
	world->entity[ENT_OBSTACLE_1].move_func = generic_move_down;
	world->entity[ENT_OBSTACLE_2].move_func = generic_move_down;
	world->entity[ENT_OBSTACLE_3].move_func = generic_move_down;
	world->entity[ENT_MUSHROOM].move_func = generic_move_down;
	world->entity[ENT_PROJECTILE_PLAYER_1].move_func = generic_move_up;
	world->entity[ENT_PROJECTILE_PLAYER_2].move_func = generic_move_up;
	world->entity[ENT_PROJECTILE_ENEMY].move_func = generic_move_down;
}

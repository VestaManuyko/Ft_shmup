#include "shmup.h"


void	score(t_player *player, Entities *target, int points)
{
	player->score += points;
	*target = ENT_NONE;
}

// void	check_destruction(t_player *player, Entities *target,
// 	int *hp, int points)
// {
// 	if (*hp > 1)
// 		(*hp)--;
// 	else
// 		score(player, target, points);
// }

bool	check_destruction(t_player *player, t_grid *unit, int points)
{
	if (unit->health > 1)
	{
		unit->health -= 1;
		return (false);
	}
	else
		score(player, &unit->entity, points);
	return (true);
}

void	player_lives_update(t_player *player)
{
	player->lives--;
	if (player->lives > 0)
		return ;
	player->dead = true;
}

void	mushroom_update_player(t_player *player)
{
	if (player->lives != LIVES_MAX)
		player->lives++;
	else
		player->score += SCORE_MUSHROOM;
}

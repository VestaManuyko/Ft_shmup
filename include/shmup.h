#pragma once

// -----------------------------------------------------------------------------
// headers
// -----------------------------------------------------------------------------

#define _GNU_SOURCE // VSCode recognition for missing POSIX stuff

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <ncurses.h>
#include <errno.h>

// -----------------------------------------------------------------------------
// macros
// -----------------------------------------------------------------------------

// ncurses
#define ESCAPE 27	// escape key
#define MIN_TERMINAL_HEIGHT 45	// minimum terminal height for the game to run
#define MIN_TERMINAL_WIDTH 130	// minimum terminal width for the game to run
#define INFOBOX_HEIGHT 3	// height of the info box at the bottom of the terminal
#define COLOR_DARK_BLACK 16	// dark black color for the background
#define COLOR_RED_ON_BLACK 1	// red text on black background
#define COLOR_RED_ON_WHITE 2	// red text on white background
#define COLOR_BLACK_ON_WHITE 3	// black text on white background
#define COLOR_PLAYER_1 4
#define COLOR_PLAYER_2 5
#define COLOR_ENEMY_STATIONARY 6
#define COLOR_ENEMY_MOVING 7
#define COLOR_ENEMY_CRAZY 8
#define COLOR_ENEMY_BOSS 9
#define COLOR_OBSTACLES 10
#define COLOR_PROJECTILE_PLAYER_1 11
#define COLOR_PROJECTILE_PLAYER_2 12
#define COLOR_PROJECTILE_ENEMY 13
#define COLOR_PROJECTILE_BOSS 14
#define COLOR_INFOBOX_BOX 15
#define COLOR_INFOBOX_TEXT 16
#define COLOR_WHITE_ON_DARK_BLACK 17
#define COLOR_MUSHROOM 18

#ifndef BONUS
# undef MIN_TERMINAL_WIDTH
# define MIN_TERMINAL_WIDTH 80	// minimum terminal width for the game to run
#endif

#define	MAX_GRID_HEIGHT (MIN_TERMINAL_HEIGHT - INFOBOX_HEIGHT)
#define MAX_GRID_WIDTH (MIN_TERMINAL_WIDTH)
#define KEY_ESCAPE 01000 // ncurses KEY_MAX = 0777
#define KEY_SPACE 01001

// game 
#define SAFE_SPACE 7	// space at the bottom of the grid without initial spawning
#define AMOUNT_OF_ENEMIES 5	// amount of enemies to spawn at the start of the game
#define AMOUNT_OF_OBSTACLES 3	// amount of obstacles to spawn at the start of the game
#define LIVES_START 5
#define LIVES_MAX 10
#define SCORE_ENEMY_STATIONARY 10	// score for killing stationary enemy
#define SCORE_ENEMY_MOVING 20	// score for killing moving enemy
#define SCORE_ENEMY_CRAZY 50	// score for killing crazy enemy
#define SCORE_BOSS 200	// score for killing boss
#define SCORE_MUSHROOM 100	// score for collecting mushroom when health is full
#define SCORE_OBSTACLE_1 5	// score for destroying obstacle 1
#define SCORE_OBSTACLE_2 10	// score for destroying obstacle 2
#define SCORE_OBSTACLE_3 1000	// score for destroying obstacle 3

// game - printable characters
#define CH_PLAYER_1 'A'
#define CH_PLAYER_2 '^'
#define CH_ENEMY_STATIONARY 'V'
#define CH_ENEMY_MOVING 'Y'
#define CH_ENEMY_CRAZY 'T'
#define CH_ENEMY_BOSS 'W'
#define CH_OBSTACLE_1 '*'	// one shot destructable obstacle
#define CH_OBSTACLE_2 '#'	// two shot destructable obstacle
#define CH_OBSTACLE_3 '@'	// almost non destructable obstacle (100 hp)
#define CH_MUSHROOM '$'
#define CH_PROJECTILE_PLAYER_1 '!'
#define CH_PROJECTILE_PLAYER_2 '.'
#define CH_PROJECTILE_ENEMY '\''
#define CH_PROJECTILE_BOSS '\"'


// game - frame control
#define FPS_LIMIT 60 // target frames per second
#define FRAME_DELAY_NONMOVING 20
#define FRAME_DELAY_POJECTILE_PLAYER 5
#define FRAME_DELAY_PROJECTILE_ENEMY 5
#define SPAWN_DELAY (2 * FRAME_DELAY_NONMOVING)
#define SHOOT_DELAY 20
#define WAVE_DELAY 700
#define NANOSECONDS_PER_SECOND 1000000000LL // 1 second in nanoseconds

// -----------------------------------------------------------------------------
// datatypes
// -----------------------------------------------------------------------------

// program states
typedef enum e_status
{
	RES_SUCCESS,
	RES_ERROR,
	RES_USER_EXIT,
	RES_GAME_OVER
}	Status;

// collection of all entities
typedef enum e_entities
{
	ENT_NONE,
	ENT_OBSTACLE_1,
	ENT_OBSTACLE_2,
	ENT_OBSTACLE_3,
	ENT_MUSHROOM,
	ENT_PLAYER_1,
	ENT_PLAYER_2,
	ENT_ENEMY_STATIONARY,
	ENT_ENEMY_MOVING,
	ENT_ENEMY_CRAZY,
	ENT_BOSS,
	ENT_PROJECTILE_PLAYER_1,
	ENT_PROJECTILE_PLAYER_2,
	ENT_PROJECTILE_ENEMY,
	ENT_PROJECTILE_BOSS,
	ENT_NUMBER_OF_ENTITIES
}	Entities;


typedef struct s_coord
{
	unsigned int y;
	unsigned int x;
}	t_coord;

// ncurses

typedef struct s_win
{
	WINDOW	*win;	// ncurses window pointer
	t_coord	size;	// window size in X and Y
	t_coord	pos;	// window position in X and Y
}	t_win;

typedef struct s_ncurses
{
	t_win	infobox;	// info box window: WINDOW *, SIZE, POSITION
	t_win	world;		// main game window: WINDOW *, SIZE, POSITION
	t_coord	term_size;	// terminal size in X and Y
	bool	colored;	// term has colors
}	t_ncurses;

typedef struct s_player
{
	t_coord	pos;	// position in the grid
	int		lives;	// lives left
	int		score;	// player score
	bool	dead;	// is player dead? (for multiplayer)
	bool	active;	// is player active? (for multiplayer)
}	t_player;

struct s_world;
// function pointer for DRAWING entities
typedef void (*t_draw_f)(t_ncurses *, int x, int y);
// function pointer for MOVING entities in vertical scrolling
typedef void (*t_move_f)(struct s_world *world, int x, int y);

// holds information needed to move entities
typedef struct s_movent
{
	unsigned int	frame_delay; // delay in frames before next move
	t_move_f		move_func; // function pointer for moving entity
}	t_movent;

// controls TIME passing for FPS and frame timing
typedef struct s_time
{
	struct timespec	start;				// time of game start
	struct timespec	last_frame;			// time of last frame
	struct timespec	frame_time_curr;	// in milliseconds
	struct timespec	frame_time_target;	// in milliseconds
	unsigned int	frame_count;		// just for info
	unsigned int	fps_curr; 			// most recent fps reached
	unsigned int	runtime;			// runtime in seconds
}	t_time;

typedef struct s_grid
{
	Entities		entity;		// entity type on that field
	unsigned int	last_frame; // current frame count for this entity
	int				health;		// health for objects & bosses
}	t_grid;

// holds all game data
typedef struct s_world
{
	// int			grid[MAX_GRID_WIDTH][MAX_GRID_HEIGHT]; // game board
	t_grid		grid[MAX_GRID_WIDTH][MAX_GRID_HEIGHT]; // game board
	t_player	player_1;		// all info about player one
	t_player	player_2;		// unused for now
	t_draw_f	draw[ENT_NUMBER_OF_ENTITIES];
	t_movent	entity[ENT_NUMBER_OF_ENTITIES];
	Status		status;			// game status
	t_time		time;			// game timer
	int			score_table[ENT_NUMBER_OF_ENTITIES];	// scores per entity type
}	t_world;

// -----------------------------------------------------------------------------
// function prototypes
// -----------------------------------------------------------------------------

// ncurses setup
Status	setup_ncurses(t_ncurses *env);
void	cleanup_ncurses(t_ncurses *env);
void	destroy_windows(t_ncurses *visual);

// ncurses windows
Status	init_windows(t_ncurses *visual);
void	erase_windows(t_ncurses *visual);
void	refresh_windows(t_ncurses *visual);

// ncurses resize
Status	resize_loop(t_ncurses *visual);
Status	terminal_too_small_loop(t_ncurses *visual);

// init
void	init_draw_pointers(t_world *world);
void	init_move_pointers(t_world *world);
void	init_scores(t_world *world);

// input
void	handle_input(int ch, t_world *world, t_ncurses *visual);

// game loop related
void	populate(t_world *world, t_ncurses *visual);
void	update_world(t_world *world);
void	check_game_over(t_world *world);
void	ask_for_restart(t_world *world, t_ncurses *visual);

// spawning
void	spawn_entities(t_world *world);
void	spawn_wave(t_world *world);
void	spawn_boss_wave(t_world *world);
void	spawn_projectile_player_1(t_world *world, t_player *player);
void	spawn_projectile_player_2(t_world *world, t_player *player);
void	spawn_projectile_enemy(t_world *world);
void	spawn_player_2(t_world *world);

// movement
void	set_new_player_coord(t_player *player, int ch,
							int left, int up, int right, int down);
void	move_player_1(t_world *world, int ch);
void	move_player_2(t_world *world, int ch);
void	generic_move_down(t_world *world, int x, int y);
void	generic_move_up(t_world *world, int x, int y);

// collision
bool	collision(t_world *world, int x, int y, Entities moving_one);
void	player_lives_update(t_player *player);
void	score(t_player *player, Entities *target, int points);
bool	check_destruction(t_player *player, t_grid *unit, int points);
void	mushroom_update_player(t_player *player);

// drawing
void	draw_game(t_world *world, t_ncurses *visual);
void	draw_entities(t_world *world, t_ncurses *visual);
void	draw_info(t_world *world, t_ncurses *visual);
void	draw_player(t_ncurses *visual, int x, int y);
void	draw_player_2(t_ncurses *visual, int x, int y);
void	draw_enemy(t_ncurses *visual, int x, int y);
void	draw_obstacle_1(t_ncurses *visual, int x, int y);
void	draw_obstacle_2(t_ncurses *visual, int x, int y);
void	draw_obstacle_3(t_ncurses *visual, int x, int y);
void	draw_mushroom(t_ncurses *visual, int x, int y);
void	draw_projectile_player(t_ncurses *visual, int x, int y);
void	draw_projectile_player_2(t_ncurses *visual, int x, int y);
void	draw_projectile_enemy(t_ncurses *visual, int x, int y);

// time
void		fps_timer(t_world *world);
void		start_timer(t_world *world);
long long	time_in_nanoseconds(struct timespec time);

// utils
unsigned int	ft_numlen(unsigned int number);
void			ft_bzero(void *s, size_t n);

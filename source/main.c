#include "shmup.h"

static void	init(t_ncurses *v, t_world *w)
{
	ft_bzero(v, sizeof (t_ncurses));
	ft_bzero(w, sizeof (t_world));
	init_draw_pointers(w);
	init_move_pointers(w);
	init_scores(w);
	srand(clock());
	start_timer(w);
	w->status = setup_ncurses(v);
}

int	main(void)
{
	t_ncurses	visual;
	t_world		world;

	world.status = RES_SUCCESS;
	while(world.status == RES_SUCCESS)
	{
		init(&visual, &world);
		if (world.status == RES_ERROR)
			exit(write(2, "Error initializing ncurses\n", 27));
		else if (world.status == RES_USER_EXIT)
			break ;
		populate(&world, &visual);
		while (world.status == RES_SUCCESS)
		{
			handle_input(wgetch(visual.world.win), &world, &visual);
			if (world.status != RES_SUCCESS)
				break ;
			update_world(&world);
			check_game_over(&world);
			fps_timer(&world);
			draw_game(&world, &visual);
		}
		ask_for_restart(&world, &visual);
	}
	cleanup_ncurses(&visual);
	if (world.status == RES_ERROR)
		exit(write(2, "Error initializing ncurses\n", 27));
	return (RES_SUCCESS);
}

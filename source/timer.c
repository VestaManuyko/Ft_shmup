#include "shmup.h"

/*
	1 second (s) = 1.000 ms = 1.000.000 µs = 1.000.000.000 ns
	1 millisecond (ms) = 1.000 µs = 1.000.000 ns
	1 microsecond (µs) = 1.000 nanoseconds
	1 FPS in ms = 1.000 ms / FPS limit
	1 FPS in ns = 1.000.000.000 ns / FPS limit

	usleep() takes MICROseconds (µs) as input
	nanosleep() takes nanoseconds (ns) as input
	clock_gettime() returns time in seconds (s) and nanoseconds (ns)
	struct timespec stores time in seconds (tv_sec) and nanoseconds (tv_nsec)
	CLOCKMONOTONIC is not affected by changes in system time
*/

static struct timespec	subtract_timespec(struct timespec a, struct timespec b);
static void				update_timers(t_world *world);
static void				sleep_until_frame_time(t_world *world);

void	fps_timer(t_world *world)
{
	(void) world;
	// usleep(10000);
	update_timers(world);
	sleep_until_frame_time(world);
	clock_gettime(CLOCK_MONOTONIC, &world->time.last_frame);
	world->time.frame_count++;
}

void	start_timer(t_world *world)
{
	long long	fps_nanoseconds;

	clock_gettime(CLOCK_MONOTONIC, &world->time.start);
	world->time.last_frame = world->time.start;
	world->time.fps_curr = 0;
	world->time.frame_count = 0;
	// calculate target frame time in nanoseconds
	fps_nanoseconds = NANOSECONDS_PER_SECOND / FPS_LIMIT;	// convert FPS limit to nanoseconds
	// seconds
	world->time.frame_time_target.tv_sec = fps_nanoseconds / NANOSECONDS_PER_SECOND;
	// nanoseconds
	world->time.frame_time_target.tv_nsec = fps_nanoseconds % NANOSECONDS_PER_SECOND;
}

long long	time_in_nanoseconds(struct timespec time)
{
	return (time.tv_sec * NANOSECONDS_PER_SECOND + time.tv_nsec);
}

static void	update_timers(t_world *world)
{
	struct timespec	now;	
	long long		frame_time_curr_in_nanoseconds;

	// get current time
	clock_gettime(CLOCK_MONOTONIC, &now);

	// calculate frame time in milliseconds
	world->time.frame_time_curr = subtract_timespec(now, world->time.last_frame);
	// calculate current FPS
	frame_time_curr_in_nanoseconds = time_in_nanoseconds(world->time.frame_time_curr);
	if (frame_time_curr_in_nanoseconds > 0)
		world->time.fps_curr = NANOSECONDS_PER_SECOND / frame_time_curr_in_nanoseconds;
	else
		world->time.fps_curr = FPS_LIMIT;
	// limit FPS counter to the defined limit
	if (world->time.fps_curr > FPS_LIMIT)
		world->time.fps_curr = FPS_LIMIT;
	// update runtime in seconds
	world->time.runtime =
		time_in_nanoseconds(subtract_timespec(now, world->time.start))
		/ NANOSECONDS_PER_SECOND;
}

// substract timespec struct B from A
static struct timespec	subtract_timespec(struct timespec a, struct timespec b)
{
	struct timespec result;

	result.tv_sec = a.tv_sec - b.tv_sec;
	result.tv_nsec = a.tv_nsec - b.tv_nsec;
	if (result.tv_nsec < 0) // adjust if nanoseconds are negative (overflow)
	{
		result.tv_sec--;
		result.tv_nsec += NANOSECONDS_PER_SECOND; // add 1 second in nanoseconds
	}
	return (result);
}

static void	sleep_until_frame_time(t_world *world)
{
	struct timespec	sleep_time;
	struct timespec	sleep_rem;

	// calculate sleep time to maintain FPS limit
	sleep_time = subtract_timespec(world->time.frame_time_target, world->time.frame_time_curr);
	if (sleep_time.tv_sec > 0
		|| (sleep_time.tv_sec == 0 && sleep_time.tv_nsec > 0))
	{
		// keep sleeping on interruption
		while (nanosleep(&sleep_time, &sleep_rem) == -1)
		{
			if (errno == EINTR)
			{
				sleep_time = sleep_rem;
			}
			else
				break ;
		}
	}
}

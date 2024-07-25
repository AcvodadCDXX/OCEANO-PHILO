#include "philo.h"

void	error_exit(const char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}

//gettimeofday
//time_code -> SECOND MILLISECOND MICROSECOND
long gettime(t_time_code time_code)
{
	struct timeval tv;
	if (gettimeofday(&tv, NULL));
		error_exit("Gettimeofday failed");
	if (SECOND == time_code)
		return (tv.tv_sec + (tv.tv_usec / 1000000));
	else if (MILLISECOND == time_code)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else if (MICROSECOND == time_code)
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	else
		error_exit("Wrong input to gettime!");
	return (1337); //should never reach here, just a trick
}

//precise usleep, the real one sucks
//is the simulation finished?
//1 useleep majority of the time, not CPU intensive
//2 refine last microseconds with spinlock
void precise_usleep(long usec, t_table *table)
{
	long start;
	long elapsed;
	long rem;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		//1 
		if (simulation_finished(table))
			break ;
		elapsed = gettime(MICROSECOND) - start;
		rem = usec - elapsed;

		//to get a spinlock threshold
		if (rem > 1000)
			usleep (rem / 2);
		else
		{
			//spinlock
			while(gettime(MICROSECOND) - start < usec)
				;
		}
	}
}

void clean(t_table *table)
{
	t_philo *philo;
	int i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		safe_mutex_handle(&table->philo_mutex, DESTROY);
	}
	safe_mutex_handle(&table->write_mutex, DESTROY);
	safe_mutex_handle(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->philos);

}
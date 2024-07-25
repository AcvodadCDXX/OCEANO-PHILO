#include "philo.h"

// [time_ms] [philo_id] [action]
//threadsafe write mutex

void write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long elapsed;


	elapsed = gettime(MILLISECOND) - philo->table->start_simulation;

	if (philo->full)
		return;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);

	if (debug)
		write_status_debug(status, philo, elapsed);
	//this is meant to be a slightly more detailed write_Status function, to be used for debugging, the
	//video creator only added some additional emojis and shit, I will remove it.
	else
	{
		if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status) && !simulation_finished(philo->table))
			printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
		else if (EATING == status && !simulation_finished(philo->table))
			printf("%-6ld %d is eating\n", elapsed, philo->id);
		else if (SLEEPING == status && !simulation_finished(philo->table))
			printf("%-6ld %d is sleeping\n", elapsed, philo->id);
		else if (THINKING == status && !simulation_finished(philo->table))
			printf("%-6ld %d is thinking\n", elapsed, philo->id);
		else if (DIED == status)
			printf("%-6ld %d %d died\n", elapsed, philo->id);
	}
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}
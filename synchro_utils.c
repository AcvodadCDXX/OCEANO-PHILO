#include "philo.h"

//spinlock to sync philo start
void wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
		;
}

//monitor busy waits untill all threads are not running

bool all_threads_running(t_mtx *mutex, long *threads, long philo_nbr)
{
	bool ret;

	ret = false;
	safe_mutex_handle(mutex, LOCK);
	if (*threads == philo_nbr)
		ret = true;
	safe_mutex_handle(mutex, UNLOCK);

	return (ret);
}

//increase threads running to sync with monitor
void increase_long(t_mtx *mutex, long *value)
{
	safe_mutex_handle(mutex, LOCK);
	(*value)++;
	safe_mutex_handle(mutex, UNLOCK);

}

//make the system fair
void desynchronize_philos(t_philo *philo)
{
	if (philo->table->philo_nbr % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(3000, philo->table);
	}
	else
	{
		if (philo->id % 2)
			thinking(philo, true)
	}
}
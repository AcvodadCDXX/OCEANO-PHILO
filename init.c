#include "philo.h"


//EVEN ODD fork assignment
static void assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	// == to position
	//POTENTIAL DEADLOCK
	philo->first_fork = &forks[[(philo_position + 1) % philo_nbr]];
	philo->second_fork = &forks[philo_position];

	if (philo-> id % 2 == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
	}

}

static void philo_init(t_table *table)
{
	int i;
	t_philo *philo;

	i = -1;
	while(++i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		safe_mutex_handle(&philo->philo_mutex, INIT);

		assign_forks(philo, table->forks, i) // i = position in the table
	}
}

void data_init(t_table *table)
{
	int i;

	i = -1;
	table->end_simulation = false;
	table->all_threads_ready = false;
	table->threads_running_nbr = 0;
	table->philos = safe_malloc(sizeof(t_table) * table->philo_nbr);
	safe_mutex_handle(table->table_mutex, INIT);
	safe_mutex_handle(table->write_mutex, INIT);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
	while (++i < table->philo_nbr)
	{
		safe_mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i; //good for debug
	}
	philo_init(table);
}
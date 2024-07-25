#include "philo.h"

//module to avoid writing LOCK UNLOCK Everywhere

//BOOL
void set_bool(t_mtx *mutex, bool *dest, bool value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

bool get_bool(t_mtx *mutex, bool *value)
{
	bool ret;

	safe_mutex_handle(mutex, LOCK);
	ret = *value;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

//LONG
long get_long(t_mtx *mutex, long *value)
{
	long ret;

	safe_mutex_handle(mutex, LOCK);
	ret = *value;
	safe_mutex_handle(mutex, UNLOCK);
	return(ret);
}

void set_long(t_mtx *mutex, long *dest, long value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

//REDUNDANT? no, used for readability
bool simulation_finished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}
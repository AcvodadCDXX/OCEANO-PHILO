#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdbool.h>
#include <pthread.h>
#include <errno.h>

//PHILO STATES
typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}			t_philo_status

//OPCODE for mutex | thread functions
typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

//codes for gettime
typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}			t_time_code;


//*structures *

typedef pthread_mutex_t t_mtx;

typedef struct s_table t_table;

//fork
struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}			t_fork;

//philo
// 5 800 200 200 [5]

struct s_philo
{
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time; // time passed from last meal.
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id; // a philo is a thread
	t_mtx		philo_mutex; // useful for races with the monitor
	t_table		*table;
}				t_philo;

//table
struct s_table
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_limit_meals; // [5] | flag if -1
	long	start_simulation;
	bool	end_simulation; // a philo dies or all philos full
	bool	all_threads_ready // sync threads
	long	threads_running_nbr;
	pthread_t monitor;
	t_mtx	table_mutex; //avoid races while reading from table
	t_mtx	write_mutex; //
	t_fork 	*forks; // array of forks
	t_philo	*philos; // array of philos
}


//FN PROTOTYPES:
//utils.c
void	error_exit(const char *error);
long gettime(t_time_code time_code);
void precise_usleep(long usec, t_table *table);
void clean(t_table *table);

//parsing.c
void parse_input(t_table *table, char **av);

//safe_functions.c
void *safe_malloc(size_t bytes);
void safe_mutex_handle(t_mtx *mutex, t_opcode op);
void safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode);

//init.c
void data_init(t_table *table);

//getters_setters.c
void set_bool(t_mtx *mutex, bool *dest, bool value);
bool get_bool(t_mtx *mutex, bool *value);
long get_long(t_mtx *mutex, long *value);
void set_long(t_mtx *mutex, long *dest, long value);
bool simulation_finished(t_table *table);

//syncrho_utils.c
void wait_all_threads(t_table *table);
bool all_threads_running(t_mtx *mutex, long *threads, long philo_nbr);
void increase_long(t_mtx *mutex, long *value);

//write.c
void write_status(t_philo_status status, t_philo *philo, bool debug);

//dinner.c
void thinking(t_philo *philo, bool pre_simulation);
void *lone_philo(void *arg);
void *dinner_simulation(void *data);
void dinner_start(t_table *table);

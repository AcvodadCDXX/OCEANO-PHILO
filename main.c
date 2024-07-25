#include "philo.h"

int main(int ac, char **av)
{
	if (5 == ac || 6 == ac)
	{
		//correct input
		//1 error checking, filling table
		parse_input(&table, av);
		//2 creating the thing
		data_init(&table);
		//3
		dinner_start(&table);
		//4 no leaks ->if philos full | 1 philo died
		clean(&table);
	}
	else
	{
		//wrong
		error_exit("Wrong input:\n Correct is ./philo 5 800 200 200 [5]\n")
	}
}
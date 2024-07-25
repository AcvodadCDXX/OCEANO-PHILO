#include "philo.h"

static bool is_digit(char c)
{
	return (c >= '0' && c <= '9')
}

static bool is_space(char c)
{
	return ((c >= 9 && c <=13) || 32 == c);
}

/*
1. check for negatives
2. check if the number is legit
"   +77%$zdkjh" is ok
"     +$^&42" is not
3. check for INT_MAX
*/

static const char *valid_input(const char *str)
{
	int len;
	const char *number;

	len = 0;
	while(is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_exit("Only positive values accepted");
	if (!is_digit(*str))
		error_exit("input is not a correct digit");
	number = str;
	while (is_digit(*str++))
		++len;
	if (len > 10)
		error_exit("The value is too big, int_max is the limit");
	return (number);

}

static long ft_atol(const char *str)
{
	long num;

	num = 0;
	str = valid_input(str);
	while(is_digit(*str))
		num = (num * 10) + (*str++ - 48);
	if (num > INT_MAX)
		error_exit("The value is too big, int_max is the limit")
	return (num);
}

//1 actual numbers
//2 not > int_max
//3 timestamps > 60ms
void parse_input(t_table *table, char **av)
{
	table->philo_nbr = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1000;
	table->time_to_eat = ft_atol(av[3]) * 1000;
	table->time_to_sleep = ft_atol(av[4]) * 1000;
	if (table->time_to_die < 60000
		|| table->time_to_sleep < 60000
		|| table->time_to_eat < 60000)
		error_exit("use timestamps >60ms")
	if (av[5])
		table->nbr_limit_meals = ft_atol(av[5]);
	else 
		table->nbr_limit_meals = -1;
}
// Your(s) program(s) should take the following arguments:

// number_of_philosophers time_to_die time_to_eat time_to_sleep
// 

// 1◦ number_of_philosophers: The number of philosophers and also the number of forks.

// 2◦ time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die milliseconds
// since the beginning of their last meal or the beginning of the simulation,
// they die.

// 3◦ time_to_eat (in milliseconds): The time it takes for a
// philosopher to eat. During that time, they will need to hold two forks.

// 4◦ time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.

// 5◦ number_of_times_each_philosopher_must_eat (optional argument): If all
// philosophers have eaten at least number_of_times_each_philosopher_must_eat
// times, the simulation stops.

// If not specified, the simulation stops when a
// philosopher dies.
// • Each philosopher has a number ranging from 1 to
// number_of_philosophers.
// • Philosopher number 1 sits next to philosopher
// number number_of_philosophers. Any other philosopher number N sits between
// philosopher number N - 1 and philosopher number N + 1.

/* Allowed functions:
 * memset, printf, malloc, free, write, usleep, gettimeofday, pthread_create,
 * pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy,
 * pthread_mutex_lock, pthread_mutex_unlock */

#include "libft_gnl/libft.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define TRUE 1
#define FALSE 0

typedef enum
{
	THINK,
	EAT,
	SLEEP,
	DIE,
}						t_action;

typedef struct s_philosopher
{
	unsigned short		id;
	unsigned short		alive;
	unsigned short		has_two_forks;
	t_action			state;
	pthread_mutex_t		*using_forks;
}						t_philosopher;

typedef struct s_table
{
	unsigned short		nb_of_philos;
	unsigned short		time_to_die;
	unsigned short		time_to_eat;
	unsigned short		time_to_sleep;
	short				times_each_must_eat;
}						t_table;

typedef struct s_meta_data
{
	t_table				*table;
	t_philosopher		*philosophers;
	pthread_mutex_t		*forks;
	int					start_time;
}						t_meta_data;

static void				print_table(t_meta_data *d);
static unsigned short	invalid_arg(int ac);
static void				free_everything(t_meta_data *data);
static t_meta_data		*create_meta_data(char **av, int ac);
static void				init_table(t_meta_data *d, char **av, int ac);
static void				create_thinkers(t_meta_data *d);
static void				print_thinkers(t_meta_data *d);
static void				print_state(t_philosopher thinker,
							long timestamp_in_ms);
static long long		get_time_in_ms(void);

long long	*get_start_time(void)
{
	struct timeval		aux;
	static int			call_counter;
	static long long	start_time;

	if (++call_counter == 1)
	{
		gettimeofday(&aux, NULL);
		start_time = (long long)aux.tv_sec * 1000000 + (long long)aux.tv_usec;
	}
	return (&start_time);
}

long long	*get_current_time(void)
{
	struct timeval		aux;
	static long long	current_time;

	gettimeofday(&aux, NULL);
	current_time = (long long)aux.tv_sec * 1000000 + (long long)aux.tv_usec;
	return (&current_time);
}

int	main(int ac, char **av)
{
	t_meta_data	*d;

	if (invalid_arg(ac))
		return (1);
	d = create_meta_data(av, ac);
	create_thinkers(d);
	free_everything(d);
}

void	create_thinkers(t_meta_data *d)
{
	int				i;
	t_philosopher	*thinker;

	i = -1;
	thinker = d->philosophers;
	while (++i < d->table->nb_of_philos)
	{
		thinker[i].id = i + 1;
		thinker[i].alive = TRUE;
		thinker[i].has_two_forks = 0;
		thinker[i].state = THINK;
	}
	print_thinkers(d);
	i = -1;
	while (++i < d->table->nb_of_philos)
	{
		usleep(100);
		print_state(thinker[i], get_time_in_ms());
	}
}

long long	get_time_in_ms(void)
{
	return (*get_current_time() - *get_start_time());
}

// print the attributes of each philosopher
static void	print_thinkers(t_meta_data *d)
{
	int				i;
	t_philosopher	*thinker;

	i = -1;
	thinker = d->philosophers;
	while (++i < d->table->nb_of_philos)
	{
		printf("thinker %d\n", i + 1);
		printf("id %d\n", thinker[i].id);
		printf("alive %d\n", thinker[i].alive);
		printf("has_two_forks %d\n", thinker[i].has_two_forks);
	}
	printf("\n\n\n\n\n");
}

void	print_state(t_philosopher thinker, long timestamp_in_ms)
{
	if (thinker.state == THINK)
		printf("%ldms %d is thinking\n", timestamp_in_ms, thinker.id);
	else if (thinker.state == EAT)
		printf("%ldms %d is eating\n", timestamp_in_ms, thinker.id);
	else if (thinker.state == SLEEP)
		printf("%ldms %d is sleeping\n", timestamp_in_ms, thinker.id);
	else if (thinker.state == DIE)
		printf("%ldms %d died\n", timestamp_in_ms, thinker.id);
}

t_meta_data	*create_meta_data(char **av, int ac)
{
	t_meta_data	*d;
	t_table		*table;
	int			i;

	i = -1;
	d = ft_calloc(sizeof(t_meta_data), 1);
	d->table = malloc(sizeof(t_table));
	table = d->table;
	init_table(d, av, ac);
	d->philosophers = malloc(sizeof(t_philosopher) * table->nb_of_philos);
	d->forks = malloc(sizeof(pthread_mutex_t) * table->nb_of_philos);
	while (++i < table->nb_of_philos)
		pthread_mutex_init(&d->forks[i], NULL);
	return (d);
}

static void	init_table(t_meta_data *d, char **av, int ac)
{
	d->table->nb_of_philos = ft_atoi(av[1]);
	d->table->time_to_die = ft_atoi(av[2]);
	d->table->time_to_eat = ft_atoi(av[3]);
	d->table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		d->table->times_each_must_eat = ft_atoi(av[5]);
	else
		d->table->times_each_must_eat = -1;
	print_table(d);
}

// prints the content of each attribute of t_table
static void	print_table(t_meta_data *d)
{
	printf("nb_of_philos %d\n", d->table->nb_of_philos);
	printf("time_to_die %d\n", d->table->time_to_die);
	printf("time_to_eat %d\n", d->table->time_to_eat);
	printf("time_to_sleep %d\n", d->table->time_to_sleep);
	printf("times_each_must_eat %d\n", d->table->times_each_must_eat);
}

static void	free_everything(t_meta_data *data)
{
	int	i;

	i = -1;
	while (++i < data->table->nb_of_philos)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->forks);
	free(data->philosophers);
	free(data->table);
	free(data);
}

static unsigned short	invalid_arg(int ac)
{
	if (ac < 5 || ac > 6)
	{
		printf("Error: wrong number of arguments\n");
		printf("Usage: [number of philosophers] [time to die] [time to "
				"eat] [time to sleep] and optional -> [number of times "
				"each philosopher must eat]\n");
		return (TRUE);
	}
	return (FALSE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_meta_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcedraz- <vcedraz-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:43:58 by vcedraz-          #+#    #+#             */
/*   Updated: 2023/09/04 09:46:48 by vcedraz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_table(t_meta_data *d, char **av, int ac);

t_meta_data	*allocate_meta_data(char **av, int ac)
{
	int			i;
	t_meta_data	*d;
	int			nb_of_philos;

	d = get_data();
	d->table = get_table();
	init_table(d, av, ac);
	nb_of_philos = d->table->nb_of_philos;
	d->threads = malloc(sizeof(pthread_t) * nb_of_philos);
	d->philosophers = malloc(sizeof(t_philosopher) * nb_of_philos);
	d->table->forks = malloc(sizeof(pthread_mutex_t) * nb_of_philos);
	i = -1;
	while (++i < d->table->nb_of_philos)
		pthread_mutex_init(&d->table->forks[i], NULL);
	pthread_mutex_init(&d->table->stdout_mutex, NULL);
	return (d);
}

static void	init_table(t_meta_data *d, char **av, int ac)
{
	d->table->nb_of_philos = ft_atoi(av[1]);
	d->table->time_to_die = ft_atoi(av[2]) + TOLERANCE;
	d->table->time_to_eat = ft_atoi(av[3]);
	d->table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		d->table->times_each_must_eat = ft_atoi(av[5]);
	else
		d->table->times_each_must_eat = -1;
}

void	free_everything(t_meta_data *data)
{
	int	i;

	i = -1;
	while (++i < data->table->nb_of_philos)
		pthread_mutex_destroy(&data->table->forks[i]);
	pthread_mutex_destroy(&data->table->stdout_mutex);
	free(data->table->forks);
	free(data->philosophers);
	free(data->threads);
	ft_lstcircular_free(&data->thinkers_circle);
}

t_meta_data	*get_data(void)
{
	static t_meta_data	d;

	return (&d);
}

t_table	*get_table(void)
{
	static t_table	table;

	return (&table);
}

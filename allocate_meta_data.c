/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_meta_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcedraz- <vcedraz-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:43:58 by vcedraz-          #+#    #+#             */
/*   Updated: 2023/08/31 08:44:11 by vcedraz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_table(t_meta_data *d, char **av, int ac);

t_meta_data	*allocate_meta_data(char **av, int ac)
{
	t_meta_data	*d;
	t_table		*table;
	int			i;

	d = ft_calloc(sizeof(t_meta_data), 1);
	d->table = malloc(sizeof(t_table));
	table = d->table;
	init_table(d, av, ac);
	d->forks = malloc(sizeof(pthread_mutex_t) * d->table->nb_of_philos);
	d->philosophers = malloc(sizeof(t_philosopher) * d->table->nb_of_philos);
	i = -1;
	while (++i < d->table->nb_of_philos)
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
	debug_print_table(d);
}

void	free_everything(t_meta_data *data)
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

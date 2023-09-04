/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thinkers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcedraz- <vcedraz-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:45:07 by vcedraz-          #+#    #+#             */
/*   Updated: 2023/08/31 08:48:05 by vcedraz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philosopher_think(t_philosopher *philo)
{
	t_table	*table;

	table = get_table();
	pthread_mutex_lock(&table->forks[philo->id]);
	pthread_mutex_lock(&table->forks[philo->id - 1]);
	philo->state = EAT;
}

void	philosopher_eat(t_philosopher *philo)
{
	usleep(get_table()->time_to_eat * 1000);
	pthread_mutex_unlock(&get_table()->forks[philo->id]);
	pthread_mutex_unlock(&get_table()->forks[philo->id - 1]);
	philo->state = SLEEP;
}

void	philosopher_sleep(t_philosopher *philo)
{
	usleep(get_table()->time_to_sleep * 1000);
	philo->state = THINK;
}

static void	*philosopher_actions_thread(void *this_philo)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)this_philo;
	while (TRUE)
	{
		output_stream(*philo, get_time_in_ms());
		if (philo->state == THINK)
			philosopher_think(philo);
		else if (philo->state == EAT)
			philosopher_eat(philo);
		else if (philo->state == SLEEP)
			philosopher_sleep(philo);
		else if (philo->state == DEAD)
			return (NULL);
	}
	return (NULL);
}

void	create_thinkers(t_meta_data *d)
{
	int				i;
	pthread_t		*threads;
	t_philosopher	*thinkers;

	i = -1;
	thinkers = d->philosophers;
	threads = malloc(sizeof(pthread_t) * d->table->nb_of_philos);
	while (++i < d->table->nb_of_philos)
	{
		thinkers[i].id = i + 1;
		thinkers[i].alive = TRUE;
		thinkers[i].state = THINK;
	}
	i = -1;
	get_start_time();
	while (++i < d->table->nb_of_philos)
		pthread_create(&threads[i], 0, philosopher_actions_thread, &thinkers[i]);
	i = -1;
	while (++i < d->table->nb_of_philos)
		pthread_join(threads[i], NULL);
}

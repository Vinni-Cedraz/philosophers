/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcedraz- <vcedraz-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:46:42 by vcedraz-          #+#    #+#             */
/*   Updated: 2023/08/31 08:48:23 by vcedraz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define RED "\033[0;31m"
#define DEF_COLOR "\033[0m"

static void	debug_output_state(t_philosopher thinker, long timestamp_in_ms)
{
	pthread_mutex_lock(&get_table()->stdout_mutex);
	if (thinker.state == THINK)
		printf(RED "%ldms %d is thinking\n" DEF_COLOR, timestamp_in_ms,
			thinker.id);
	else if (thinker.state == EAT)
		printf(RED "%ldms %d is eating\n" DEF_COLOR, timestamp_in_ms,
			thinker.id);
	else if (thinker.state == SLEEP)
		printf(RED "%ldms %d is sleeping\n" DEF_COLOR, timestamp_in_ms,
			thinker.id);
	else if (thinker.state == DEAD)
		printf(RED "%ldms %d died\n" DEF_COLOR, timestamp_in_ms, thinker.id);
	pthread_mutex_unlock(&get_table()->stdout_mutex);
}

// print the attributes of each philosopher
void	debug_print_thinkers(t_meta_data *d)
{
	int				i;
	t_philosopher	*thinker;

	i = -1;
	thinker = d->philosophers;
	while (++i < d->table->nb_of_philos)
	{
		printf("thinker %d\n", i + 1);
		printf("id %d\n", thinker[i].id);
		debug_output_state(thinker[i], get_time_in_ms());
		printf("id %d has eaten %d times\n", thinker[i].id,
			thinker[i].nb_of_meals);
	}
	printf("\n\n\n\n\n");
}

// prints the content of each attribute of t_table
void	debug_print_table(t_meta_data *d)
{
	printf("nb_of_philos %d\n", d->table->nb_of_philos);
	printf("time_to_die %d\n", d->table->time_to_die);
	printf("time_to_eat %d\n", d->table->time_to_eat);
	printf("time_to_sleep %d\n", d->table->time_to_sleep);
	printf("times_each_must_eat %d\n", d->table->times_each_must_eat);
}

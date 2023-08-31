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

void	create_thinkers(t_meta_data *d)
{
	int				i;
	t_philosopher	*thinkers;

	i = -1;
	thinkers = d->philosophers;
	while (++i < d->table->nb_of_philos)
	{
		thinkers[i].id = i + 1;
		thinkers[i].alive = TRUE;
		thinkers[i].has_two_forks = 0;
		thinkers[i].state = THINK;
		thinkers[i].using_forks = NULL;
	}
	i = -1;
	get_start_time();
	while (++i < d->table->nb_of_philos)
	{
		usleep(d->table->time_to_eat * 1000);
		output_stream(thinkers[i], get_time_in_ms());
	}
}

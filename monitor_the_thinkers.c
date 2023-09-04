/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_the_thinkers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcedraz- <vcedraz-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:50:32 by vcedraz-          #+#    #+#             */
/*   Updated: 2023/09/04 11:54:24 by vcedraz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void			*all_are_satisfied(void);

void	*monitor_the_thinkers(void *thinkers)
{
	t_philosopher	*this_thinker;
	int				times_each_must_eat;
	int				satisfied_philos;

	satisfied_philos = 0;
	times_each_must_eat = get_table()->times_each_must_eat;
	while (TRUE)
	{
		this_thinker = (t_philosopher *)((t_node *)(thinkers))->content;
		if (this_thinker->state == DEAD)
		{
			pthread_mutex_lock(&get_table()->stdout_mutex);
			output_stream(*this_thinker, get_time_in_ms());
			pthread_mutex_unlock(&get_table()->stdout_mutex);
			return (NULL);
		}
		else if (this_thinker->nb_of_meals == times_each_must_eat)
		{
			this_thinker->state = SATISFIED;
			if (++satisfied_philos == get_table()->nb_of_philos)
				return (all_are_satisfied());
		}
		thinkers = ((t_node *)(thinkers))->next;
	}
}

static inline void	*all_are_satisfied(void)
{
	pthread_mutex_lock(&get_table()->stdout_mutex);
	get_data()->all_are_satisfied = TRUE;
	pthread_mutex_unlock(&get_table()->stdout_mutex);
	return (NULL);
}

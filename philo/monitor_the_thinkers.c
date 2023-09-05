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

static short		monitor_satisfaction(t_node *thinkers);

void	*monitor_the_thinkers(void *thinkers)
{
	t_philosopher	*this_thinker;
	int				times_each_must_eat;
	int				death_time;

	death_time = get_table()->time_to_die;
	times_each_must_eat = get_table()->times_each_must_eat;
	while (TRUE)
	{
		this_thinker = ((t_node *)(thinkers))->philosopher;
		if (this_thinker->nb_of_meals == times_each_must_eat)
		{
			this_thinker->state = SATISFIED;
			if (monitor_satisfaction(thinkers))
				return (terminate_all_threads());
		}
		else if (get_time_in_ms() - this_thinker->last_meal_time >= death_time)
		{
			this_thinker->state = DEAD;
			output_state(*this_thinker, get_time_in_ms());
			return (terminate_all_threads());
		}
		thinkers = ((t_node *)(thinkers))->next;
	}
}

static inline short	monitor_satisfaction(t_node *thinkers)
{
	t_philosopher	*this_thinker;
	t_node			*head;

	head = thinkers->next;
	while (head != thinkers)
	{
		this_thinker = head->philosopher;
		if (this_thinker->state != SATISFIED)
			return (FALSE);
		head = head->next;
	}
	return (TRUE);
}

inline void	*terminate_all_threads(void)
{
	int	i;

	i = -1;
	if (get_data()->detached_threads)
		return (NULL);
	get_data()->detached_threads = TRUE;
	while (++i < get_table()->nb_of_philos)
		pthread_detach(get_data()->threads[i]);
	free_everything(get_data());
	return (NULL);
}

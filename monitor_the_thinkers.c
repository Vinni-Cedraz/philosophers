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
static void			*terminate_all_threads(void);

void	*monitor_the_thinkers(void *thinkers)
{
	t_philosopher	*this_thinker;
	int				times_each_must_eat;

	times_each_must_eat = get_table()->times_each_must_eat;
	while (TRUE)
	{
		this_thinker = (t_philosopher *)((t_node *)(thinkers))->content;
		if (this_thinker->state == DEAD)
		{
			pthread_mutex_lock(&get_table()->stdout_mutex);
			output_state(*this_thinker, get_time_in_ms());
			pthread_mutex_unlock(&get_table()->stdout_mutex);
			return (NULL);
		}
		else if (this_thinker->nb_of_meals == times_each_must_eat)
		{
			this_thinker->state = SATISFIED;
			if (monitor_satisfaction(thinkers))
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
		this_thinker = (t_philosopher *)head->content;
		if (this_thinker->state != SATISFIED)
			return (FALSE);
		head = head->next;
	}
	return (TRUE);
}

// force pthread_detach on all threads of the d->threads array
static inline void	*terminate_all_threads(void)
{
	int	i;

	i = -1;
	while (++i < get_table()->nb_of_philos)
		pthread_detach(get_data()->threads[i]);
	get_data()->detached_threads = TRUE;
	return (NULL);
}

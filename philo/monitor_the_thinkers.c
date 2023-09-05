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
	int				time_to_die;

	time_to_die = get_table()->time_to_die;
	while (FALSE == get_data()->stop_the_simulation)
	{
		this_thinker = ((t_node *)(thinkers))->philosopher;
		if (get_time_in_ms() - this_thinker->last_meal_time > time_to_die)
		{
			get_data()->stop_the_simulation = TRUE;
			this_thinker->state = DEAD;
		}
		else if (this_thinker->satisfied == TRUE)
			monitor_satisfaction(thinkers);
		thinkers = ((t_node *)(thinkers))->next;
	}
	return (NULL);
}

static inline short	monitor_satisfaction(t_node *thinkers)
{
	t_philosopher	*this_thinker;
	t_node			*head;

	head = thinkers->next;
	while (head != thinkers)
	{
		this_thinker = head->philosopher;
		if (this_thinker->satisfied == FALSE)
			return (FALSE);
		head = head->next;
	}
	get_data()->stop_the_simulation = TRUE;
	return (TRUE);
}

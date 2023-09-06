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

static short		all_are_satisfied(t_node *thinkers);

void	*monitor_the_thinkers(void *thinkers)
{
	t_philosopher	*this_thinker;

	while (TRUE)
	{
		this_thinker = ((t_node *)(thinkers))->philosopher;
		check_if_philo_is_dying(this_thinker);
		if (this_thinker->is_dying)
		{
			get_data()->stop_the_simulation = TRUE;
			this_thinker->state = DEAD;
			output_state(*this_thinker, get_time_in_ms(this_thinker));
			return (NULL);
		}
		else if (this_thinker->satisfied)
		{
			if (all_are_satisfied(thinkers) == TRUE)
				return (NULL);
		}
		thinkers = ((t_node *)(thinkers))->next;
	}
}

static inline short	all_are_satisfied(t_node *thinkers)
{
	t_philosopher	*this_thinker;
	t_node			*head;

	head = thinkers->next;
	while (head != thinkers)
	{
		this_thinker = head->philosopher;
		if (this_thinker->satisfied != TRUE)
			return (FALSE);
		head = head->next;
	}
	get_data()->stop_the_simulation = TRUE;
	return (TRUE);
}

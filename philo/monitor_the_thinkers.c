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

static void			monitor_satisfaction(t_node *thinkers);
static void			check_death(t_philosopher *this_thinker);
static void			check_satisfaction(t_philosopher *this_thinker);

void	*monitor_the_thinkers(void *thinkers)
{
	t_philosopher				*this_thinker;
	static const t_funct_ptr	action[2] = {check_death, check_satisfaction};

	while (FALSE == get_data()->stop_the_simulation)
	{
		this_thinker = ((t_node *)(thinkers))->philosopher;
		action[this_thinker->satisfied](this_thinker);
		thinkers = ((t_node *)(thinkers))->next;
	}
	return (NULL);
}

static void	check_satisfaction(t_philosopher *this_thinker)
{
	(void)this_thinker;
	monitor_satisfaction(get_data()->thinkers_circle);
}

static void	check_death(t_philosopher *this_thinker)
{
	long long	time_to_die;

	time_to_die = get_table()->time_to_die;
	if (get_time_in_ms() - this_thinker->last_meal_time > time_to_die)
	{
		get_data()->stop_the_simulation = TRUE;
		this_thinker->state = DEAD;
		output_state(*this_thinker, get_time_in_ms());
	}
}

static inline void	monitor_satisfaction(t_node *thinkers)
{
	t_philosopher	*this_thinker;
	t_node			*head;

	head = thinkers->next;
	while (head != thinkers)
	{
		this_thinker = head->philosopher;
		if (this_thinker->satisfied == FALSE)
			return ;
		head = head->next;
	}
	get_data()->stop_the_simulation = TRUE;
}

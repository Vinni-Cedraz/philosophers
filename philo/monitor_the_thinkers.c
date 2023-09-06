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

static void	check_if_philo_is_dying(t_philosopher *philo);
static void	check_satisfaction_of_all_thinkers(t_philosopher *this_thinker);

void	monitor_the_thinkers(void *thinkers)
{
	t_philosopher				*this_thinker;
	static const t_funct_ptr	check[2] = {
		check_if_philo_is_dying, check_satisfaction_of_all_thinkers
	};

	while (FALSE == get_data()->stop_the_simulation)
	{
		this_thinker = ((t_node *)(thinkers))->philosopher;
		check[this_thinker->is_satisfied](this_thinker);
		thinkers = ((t_node *)(thinkers))->next;
	}
}

static inline void	check_if_philo_is_dying(t_philosopher *philo)
{
	time_t	current_time;
	time_t	time_to_die;

	time_to_die = get_table()->time_to_die;
	current_time = get_time_in_ms(philo);
	if (current_time - philo->last_meal_time >= time_to_die)
	{
		philo->state = DEAD;
		output_state(*philo, get_time_in_ms(philo));
		get_data()->stop_the_simulation = TRUE;
	}
}

static void	check_satisfaction_of_all_thinkers(t_philosopher *this_thinker)
{
	t_node	*head;
	t_node	*tail;

	head = get_data()->thinkers_circle;
	tail = head->next;
	while (head != tail)
	{
		this_thinker = tail->philosopher;
		if (this_thinker->is_satisfied != TRUE)
			return ;
		tail = tail->next;
	}
	get_data()->stop_the_simulation = TRUE;
}

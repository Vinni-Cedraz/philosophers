/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_thread_callback.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcedraz- <vcedraz-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 09:11:07 by vcedraz-          #+#    #+#             */
/*   Updated: 2023/09/05 09:12:20 by vcedraz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

inline void	*philo_thread_callback(void *this_philo)
{
	t_philosopher				*philo;
	static const t_funct_ptr	action[4] = {
		philosopher_think, philosopher_eat, philosopher_sleep, philosopher_die,
	};

	philo = (t_philosopher *)this_philo;
	philo->start_time = get_time();
	while (!get_data()->stop_the_simulation && !philo->is_satisfied)
		action[philo->state](philo);
	return (NULL);
}

inline void	advance_philo_to_next_state(t_philosopher *philo)
{
	static const int	next_state[3] = {EAT, SLEEP, THINK};

	if (DEAD == philo->state)
		return ;
	philo->state = next_state[philo->state];
}

inline t_bool	this_philo_is_hungry(t_philosopher *philo)
{
	const t_bool	hungry = philo->nb_of_meals++ != get_data()->limit_of_meals;

	if (!hungry)
		philo->is_satisfied = TRUE;
	return (hungry);
}

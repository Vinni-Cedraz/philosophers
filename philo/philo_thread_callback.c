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

void	*philo_thread_callback(void *this_philo)
{
	t_philosopher						*philo;
	static const t_fptr_philo_action	action[5] = {
		philosopher_think,
		philosopher_eat,
		philosopher_sleep,
		philosopher_dead,
		philosopher_dead
	};

	philo = (t_philosopher *)this_philo;
	while (!get_data()->detached_threads)
	{
		output_state(*philo, get_time_in_ms());
		action[philo->state](philo);
	}
	return (NULL);
}

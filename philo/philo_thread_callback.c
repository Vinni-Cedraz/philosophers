/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread_callback.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcedraz- <vcedraz-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 09:11:07 by vcedraz-          #+#    #+#             */
/*   Updated: 2023/09/07 17:45:29 by vcedraz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

inline void	*philo_thread_callback(void *this_philo)
{
	t_philosopher				*philo;
	static const t_funct_ptr	action[4] = {
		philosopher_think,
		philosopher_eat,
		philosopher_sleep,
		philosopher_dead,
	};

	philo = (t_philosopher *)this_philo;
	philo->start_time = get_time();
	while (!philo->is_satisfied && !get_data()->stop_the_simulation)
	{
		action[philo->state](philo);
	}
	return (NULL);
}

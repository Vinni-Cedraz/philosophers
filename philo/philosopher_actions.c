/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcedraz- <vcedraz-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 09:05:57 by vcedraz-          #+#    #+#             */
/*   Updated: 2023/09/05 12:40:58 by vcedraz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

inline void	philosopher_think(t_philosopher *philo)
{
	output_state(*philo, get_time_in_ms(philo));
	advance_philo_to_next_state(philo);
}

inline void	philosopher_eat(t_philosopher *philo)
{
	if (!this_philo_is_hungry(philo))
		return ;
	lock_unlock_forks(philo, LOCK);
	if (get_data()->stop_the_simulation || philo->state == DEAD)
		return (lock_unlock_forks(philo, UNLOCK));
	output_state(*philo, get_time_in_ms(philo));
	philo->last_meal_time = get_time_in_ms(philo);
	usleep(get_data()->time_to_eat * 1000);
	lock_unlock_forks(philo, UNLOCK);
	advance_philo_to_next_state(philo);
}

inline void	philosopher_sleep(t_philosopher *philo)
{
	output_state(*philo, get_time_in_ms(philo));
	usleep(get_data()->time_to_sleep * 1000);
	advance_philo_to_next_state(philo);
}

inline void	philo_starves_alone(t_philosopher *philo)
{
	usleep(get_data()->time_to_die * 1000);
	philosopher_die(philo);
	output_state(*philo, get_time_in_ms(philo));
	get_data()->stop_the_simulation = TRUE;
}

inline void	philosopher_die(t_philosopher *philo)
{
	philo->state = DEAD;
	return ;
}

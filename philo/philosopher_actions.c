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
	output_state(*philo, get_time_in_ms());
	philo->state = EAT;
}

inline void	philosopher_eat(t_philosopher *philo)
{
	if (philo->nb_of_meals++ == get_table()->times_each_must_eat)
	{
		philo->satisfied = TRUE;
		return ;
	}
	philo->last_meal_time = get_time_in_ms();
	lock_unlock_forks(philo, LOCK);
	if (philo->state != DEAD)
		output_state(*philo, get_time_in_ms());
	usleep(get_table()->time_to_eat * 1000);
	lock_unlock_forks(philo, UNLOCK);
	philo->state = SLEEP;
}

inline void	philosopher_sleep(t_philosopher *philo)
{
	output_state(*philo, get_time_in_ms());
	usleep(get_table()->time_to_sleep * 1000);
	philo->state = THINK;
}

inline void	philo_starves_alone(t_philosopher *philo)
{
	usleep(get_table()->time_to_die * 1000);
	philo->state = DEAD;
}

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

static inline unsigned short	check_if_philo_is_dying(t_philosopher *philo,
									int eat);

inline void	philosopher_think(t_philosopher *philo)
{
	if (check_if_philo_is_dying(philo, FALSE))
		return ;
	output_state(*philo, get_time_in_ms(philo));
	philo->state = EAT;
}

inline void	philosopher_eat(t_philosopher *philo)
{
	if (philo->nb_of_meals++ == get_data()->times_each_must_eat)
	{
		philo->is_satisfied = TRUE;
		return ;
	}
	catch_or_put_down_forks(philo, CATCH);
	if (check_if_philo_is_dying(philo, TRUE))
		return ;
	if (philo->state != DEAD)
		output_state(*philo, get_time_in_ms(philo));
	philo->last_meal_time = get_time_in_ms(philo);
	usleep(get_data()->time_to_eat * 1000);
	catch_or_put_down_forks(philo, PUT_DOWN);
	if (philo->state != DEAD)
		philo->state = SLEEP;
}

inline void	philosopher_sleep(t_philosopher *philo)
{
	if (check_if_philo_is_dying(philo, FALSE))
		return ;
	output_state(*philo, get_time_in_ms(philo));
	usleep(get_data()->time_to_sleep * 1000);
	philo->state = THINK;
}

inline void	philo_starves_alone(t_philosopher *philo)
{
	usleep(get_data()->time_to_die * 1000);
	philo->state = DEAD;
}

static inline unsigned short	check_if_philo_is_dying(t_philosopher *philo,
		int eat)
{
	static _Atomic unsigned short	dying = FALSE;
	time_t							current_time;
	time_t							time_to_die;

	if (dying == TRUE && eat)
	{
		catch_or_put_down_forks(philo, PUT_DOWN);
		return (dying);
	}
	time_to_die = get_data()->time_to_die;
	current_time = get_time_in_ms(philo);
	dying = get_data()->stop_the_simulation;
	if (current_time - philo->last_meal_time >= time_to_die)
	{
		dying = TRUE;
		philo->state = DEAD;
		if (eat)
			catch_or_put_down_forks(philo, PUT_DOWN);
		get_data()->stop_the_simulation = TRUE;
	}
	return (dying);
}

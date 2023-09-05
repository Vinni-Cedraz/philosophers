/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcedraz- <vcedraz-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 09:05:57 by vcedraz-          #+#    #+#             */
/*   Updated: 2023/09/05 09:06:28 by vcedraz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

inline void	philosopher_think(t_philosopher *philo)
{
	int	right_fork_idx;
	int	left_fork_idx;

	right_fork_idx = philo->id;
	left_fork_idx = philo->id - 1;
	if (-1 == left_fork_idx)
		left_fork_idx = get_table()->nb_of_philos - 1;
	if (philo->id & 1)
	{
		pthread_mutex_lock(&get_table()->forks[right_fork_idx]);
		pthread_mutex_lock(&get_table()->forks[left_fork_idx]);
	}
	else
	{
		pthread_mutex_lock(&get_table()->forks[left_fork_idx]);
		pthread_mutex_lock(&get_table()->forks[right_fork_idx]);
	}
	philo->state = EAT;
}

inline void	philosopher_eat(t_philosopher *philo)
{
	int	right_fork_idx;
	int	left_fork_idx;

	right_fork_idx = philo->id;
	left_fork_idx = philo->id - 1;
	philo->last_meal_time = get_time_in_ms();
	usleep(get_table()->time_to_eat * 1000);
	if (-1 == left_fork_idx)
		left_fork_idx = get_table()->nb_of_philos - 1;
	if (philo->id & 1)
	{
		pthread_mutex_unlock(&get_table()->forks[right_fork_idx]);
		pthread_mutex_unlock(&get_table()->forks[left_fork_idx]);
	}
	else
	{
		pthread_mutex_unlock(&get_table()->forks[left_fork_idx]);
		pthread_mutex_unlock(&get_table()->forks[right_fork_idx]);
	}
	philo->nb_of_meals++;
	philo->state = SLEEP;
}

inline void	philosopher_sleep(t_philosopher *philo)
{
	usleep(get_table()->time_to_sleep * 1000);
	philo->state = THINK;
}

inline void	philosopher_dead(t_philosopher *philo)
{
	(void)philo;
	if (!get_data()->detached_threads)
		terminate_all_threads();
}

inline void	philosopher_satisfied(t_philosopher *philo)
{
	(void)philo;
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   each_philosopher_actions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcedraz- <vcedraz-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 09:11:17 by vcedraz-          #+#    #+#             */
/*   Updated: 2023/09/04 11:53:29 by vcedraz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void			philosopher_think(t_philosopher *philo);
static void			philosopher_eat(t_philosopher *philo);
static void			philosopher_sleep(t_philosopher *philo);

void	*each_philosopher_actions(void *this_philo)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)this_philo;
	while (TRUE)
	{
		output_state(*philo, get_time_in_ms());
		if (philo->state == THINK)
			philosopher_think(philo);
		else if (philo->state == EAT)
			philosopher_eat(philo);
		else if (philo->state == SLEEP)
			philosopher_sleep(philo);
		else if (philo->state == DEAD)
			return (NULL);
	}
}

static inline void	philosopher_think(t_philosopher *philo)
{
	int	right_fork_idx;
	int	left_fork_idx;

	right_fork_idx = philo->id;
	left_fork_idx = philo->id - 1;
	if (-1 == left_fork_idx)
	{
		left_fork_idx = get_table()->nb_of_philos - 1;
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

static inline void	philosopher_eat(t_philosopher *philo)
{
	int	right_fork_idx;
	int	left_fork_idx;

	right_fork_idx = philo->id;
	left_fork_idx = philo->id - 1;
	philo->last_meal_time = get_time_in_ms();
	usleep(get_table()->time_to_eat * 1000);
	if (-1 == left_fork_idx)
	{
		left_fork_idx = get_table()->nb_of_philos - 1;
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

static inline void	philosopher_sleep(t_philosopher *philo)
{
	usleep(get_table()->time_to_sleep * 1000);
	philo->state = THINK;
}

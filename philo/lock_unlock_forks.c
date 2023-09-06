/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_unlock_forks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcedraz- <vcedraz-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:15:33 by vcedraz-          #+#    #+#             */
/*   Updated: 2023/09/05 12:44:29 by vcedraz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lock_left_handed(t_philosopher *philo);
static void	lock_right_handed(t_philosopher *philo);
static void	unlock_left_handed(t_philosopher *philo);
static void	unlock_right_handed(t_philosopher *philo);

void	lock_unlock_forks(t_philosopher *philo, int lock_unlock)
{
	static const t_funct_ptr	action[2][3] = {
	{lock_left_handed, lock_right_handed, philo_starves_alone},
	{unlock_left_handed, unlock_right_handed, philo_starves_alone},
	};

	action[lock_unlock][philo->is_right_handed](philo);
}

static void	lock_left_handed(t_philosopher *philo)
{
	pthread_mutex_lock(&get_table()->forks[philo->left_fork_idx]);
	pthread_mutex_lock(&get_table()->forks[philo->right_fork_idx]);
}

static void	unlock_left_handed(t_philosopher *philo)
{
	pthread_mutex_unlock(&get_table()->forks[philo->left_fork_idx]);
	pthread_mutex_unlock(&get_table()->forks[philo->right_fork_idx]);
}

static void	lock_right_handed(t_philosopher *philo)
{
	pthread_mutex_lock(&get_table()->forks[philo->right_fork_idx]);
	pthread_mutex_lock(&get_table()->forks[philo->left_fork_idx]);
}

static void	unlock_right_handed(t_philosopher *philo)
{
	pthread_mutex_unlock(&get_table()->forks[philo->right_fork_idx]);
	pthread_mutex_unlock(&get_table()->forks[philo->left_fork_idx]);
}

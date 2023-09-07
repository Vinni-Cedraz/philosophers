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

static void	catch_left_fork_first(t_philosopher *philo);
static void	catch_right_fork_first(t_philosopher *philo);
static void	put_down_left_fork_first(t_philosopher *philo);
static void	put_down_right_fork_first(t_philosopher *philo);

inline void	catch_or_put_down_forks(t_philosopher *philo, int catch)
{
	static const t_funct_ptr	action[2][3] = {
	{put_down_left_fork_first, put_down_right_fork_first, philo_starves_alone},
	{catch_left_fork_first, catch_right_fork_first, philo_starves_alone},
	};

	action[catch][philo->is_right_handed + philo->single_philo_at_table](philo);
}

static inline void	catch_left_fork_first(t_philosopher *philo)
{
	pthread_mutex_lock(&get_table()->forks[philo->left_fork_idx]);
	pthread_mutex_lock(&get_table()->forks[philo->right_fork_idx]);
}

static inline void	put_down_left_fork_first(t_philosopher *philo)
{
	pthread_mutex_unlock(&get_table()->forks[philo->left_fork_idx]);
	pthread_mutex_unlock(&get_table()->forks[philo->right_fork_idx]);
}

static inline void	catch_right_fork_first(t_philosopher *philo)
{
	pthread_mutex_lock(&get_table()->forks[philo->right_fork_idx]);
	pthread_mutex_lock(&get_table()->forks[philo->left_fork_idx]);
}

static inline void	put_down_right_fork_first(t_philosopher *philo)
{
	pthread_mutex_unlock(&get_table()->forks[philo->right_fork_idx]);
	pthread_mutex_unlock(&get_table()->forks[philo->left_fork_idx]);
}

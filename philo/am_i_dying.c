/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   am_i_dying.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcedraz- <vcedraz-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:36:14 by vcedraz-          #+#    #+#             */
/*   Updated: 2023/09/07 17:38:30 by vcedraz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	am_i_dying(t_philosopher *philo, int eat)
{
	static _Atomic t_bool			dying = FALSE;
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

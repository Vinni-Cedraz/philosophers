/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcedraz- <vcedraz-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 22:23:38 by vcedraz-          #+#    #+#             */
/*   Updated: 2023/09/04 22:23:39 by vcedraz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

inline void	output_state(t_philosopher thinker, long timestamp_in_ms)
{
	_Atomic static int	someone_died;

	if (thinker.state == DEAD)
	{
		someone_died++;
		printf("%ldms %d died\n", timestamp_in_ms, thinker.id);
	}
	if (1 == someone_died)
		return ;
	pthread_mutex_lock(&get_table()->stdout_mutex);
	if (thinker.state == THINK)
		printf("%ldms %d is thinking\n", timestamp_in_ms, thinker.id);
	else if (thinker.state == EAT)
		printf("%ldms %d is eating\n", timestamp_in_ms, thinker.id);
	else if (thinker.state == SLEEP)
		printf("%ldms %d is sleeping\n", timestamp_in_ms, thinker.id);
	pthread_mutex_unlock(&get_table()->stdout_mutex);
}

inline unsigned short	invalid_arg(int ac)
{
	if (ac < 5 || ac > 6)
	{
		printf("%s%s%s\n", E_MSG, USAGE_MSG, USAGE_MSG);
		return (TRUE);
	}
	return (FALSE);
}

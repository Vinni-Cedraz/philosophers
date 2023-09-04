/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_stream.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcedraz- <vcedraz-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:52:19 by vcedraz-          #+#    #+#             */
/*   Updated: 2023/08/31 08:52:46 by vcedraz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	output_state(t_philosopher thinker, long timestamp_in_ms)
{
	pthread_mutex_lock(&get_table()->stdout_mutex);
	if (thinker.state == THINK)
		printf("%ldms %d is thinking\n", timestamp_in_ms, thinker.id);
	else if (thinker.state == EAT)
		printf("%ldms %d is eating\n", timestamp_in_ms, thinker.id);
	else if (thinker.state == SLEEP)
		printf("%ldms %d is sleeping\n", timestamp_in_ms, thinker.id);
	else if (thinker.state == DEAD)
		printf("%ldms %d died\n", timestamp_in_ms, thinker.id);
	pthread_mutex_unlock(&get_table()->stdout_mutex);
}

unsigned short	invalid_arg(int ac)
{
	if (ac < 5 || ac > 6)
	{
		printf("%s%s%s\n", E_MSG, USAGE_MSG, USAGE_MSG);
		return (TRUE);
	}
	return (FALSE);
}

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
	static const char	*msgs[] = {
		THINKING, EATING, SLEEPING, DIED
	};

	if (TRUE == get_data()->stop_the_simulation)
		return ;
	pthread_mutex_lock(&get_table()->stdout_mutex);
	printf(msgs[thinker.state], timestamp_in_ms, thinker.id);
	pthread_mutex_unlock(&get_table()->stdout_mutex);
}

inline unsigned short	invalid_arg(int ac)
{
	if (ac < 5 || ac > 6)
	{
		printf("%s\n", E_MSG);
		return (TRUE);
	}
	return (FALSE);
}

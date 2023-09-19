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

	pthread_mutex_lock(&get_data()->stdout_mutex);
	printf(msgs[thinker.state], timestamp_in_ms, thinker.id);
	pthread_mutex_unlock(&get_data()->stdout_mutex);
}

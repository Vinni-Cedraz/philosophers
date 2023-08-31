/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time_in_ms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcedraz- <vcedraz-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:39:24 by vcedraz-          #+#    #+#             */
/*   Updated: 2023/08/31 08:39:25 by vcedraz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline long long	*get_start_time(void);
static inline long long	*get_current_time(void);

long long	get_time_in_ms(void)
{
	return (*get_current_time() - *get_start_time());
}

static inline long long	*get_start_time(void)
{
	struct timeval		aux;
	static int			call_counter;
	static long long	start_time;

	if (++call_counter == 1)
	{
		gettimeofday(&aux, NULL);
		start_time = (long long)aux.tv_sec * 1000000 + (long long)aux.tv_usec;
	}
	return (&start_time);
}

static inline long long	*get_current_time(void)
{
	struct timeval		aux;
	static long long	current_time;

	gettimeofday(&aux, NULL);
	current_time = (long long)aux.tv_sec * 1000000 + (long long)aux.tv_usec;
	return (&current_time);
}

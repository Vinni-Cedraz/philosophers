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

static long long			get_milissecs(struct timeval *aux);

static _Atomic long long	*get_current_time(void);

inline long long	get_time_in_ms(void)
{
	return (*get_current_time() - *get_start_time());
}

inline _Atomic long long	*get_start_time(void)
{
	struct timeval				aux;
	_Atomic static int			call_counter;
	_Atomic static long long	start_time;

	if (++call_counter == 1)
	{
		gettimeofday(&aux, NULL);
		start_time = get_milissecs(&aux);
	}
	return (&start_time);
}

static inline _Atomic long long	*get_current_time(void)
{
	struct timeval				aux;
	_Atomic static long long	current_time;

	gettimeofday(&aux, NULL);
	current_time = get_milissecs(&aux);
	return (&current_time);
}

static inline long long	get_milissecs(struct timeval *aux)
{
	return ((long long)aux->tv_sec * 1000 + (long long)aux->tv_usec / 1000);
}
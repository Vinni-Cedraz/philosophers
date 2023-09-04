/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcedraz- <vcedraz-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:33:54 by vcedraz-          #+#    #+#             */
/*   Updated: 2023/08/31 08:47:46 by vcedraz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft_gnl/libft.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0

# define E_MSG "Error: wrong number of arguments\nUsage: [number of philosopher"
# define USAGE_MSG "s] [time to die] [time to eat] [time to sleep] and"
# define OPT_USAGE "optional -> [number of times each philosopher must eat]\n"

typedef struct s_tab	t_table;
typedef struct s_philo	t_philosopher;

typedef enum e_action
{
	THINK,
	EAT,
	SLEEP,
	DEAD,
}						t_action;

typedef struct s_meta_data
{
	t_table				*table;
	t_philosopher		*philosophers;
	int					start_time;
}						t_meta_data;

typedef struct s_tab
{
	unsigned short		nb_of_philos;
	unsigned short		time_to_die;
	unsigned short		time_to_eat;
	unsigned short		time_to_sleep;
	pthread_mutex_t		*forks;
	short				times_each_must_eat;
	pthread_mutex_t		stdout_mutex;
}						t_table;

typedef struct s_philo
{
	unsigned short		id;
	unsigned short		alive;
	t_action			state;
	unsigned short		last_meal_time;
	unsigned short		nb_of_meals;
}						t_philosopher;

_Atomic long long 		*get_start_time(void);
void					debug_print_table(t_meta_data *d);
unsigned short			invalid_arg(int ac);
t_meta_data				*allocate_meta_data(char **av, int ac);
void					create_thinkers(t_meta_data *d);
void					output_stream(t_philosopher thinker, long timestamp);
long long				get_time_in_ms(void);
void					free_everything(t_meta_data *data);
t_table					*get_table(void);
t_meta_data				*get_data(void);
#endif

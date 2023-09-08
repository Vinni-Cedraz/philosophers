/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcedraz- <vcedraz-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:33:54 by vcedraz-          #+#    #+#             */
/*   Updated: 2023/09/05 12:44:56 by vcedraz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0
# define LOCK 1
# define UNLOCK 0
# define LEFT 0
# define RIGHT 1
# define TOLERANCE 3

# define ERROR_MSG "Error: wrong arguments\n"
# define ARG_MSG_1 "Expected arguments: number_of_philosophers"
# define ARG_MSG_2 " time_to_die time_to_eat time_to_sleep and optional ->"
# define ARG_MSG_3 " number_of_times_each_philosopher_must_eat"

# define THINKING "%ldms %d is thinking\n"
# define EATING "%ldms %d is eating\n"
# define SLEEPING "%ldms %d sleep\n"
# define DIED "%ldms %d died\n"

typedef struct s_tab	t_table;
typedef struct s_philo	t_philosopher;
typedef void			(*t_funct_ptr)(t_philosopher *);
typedef unsigned short	t_bool;

typedef struct s_node
{
	t_philosopher		*philosopher;
	struct s_node		*next;
}						t_node;

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
	pthread_t			*threads;
	pthread_mutex_t		stdout_mutex;
	time_t				time_to_die;
	unsigned short		time_to_eat;
	unsigned short		time_to_sleep;
	_Atomic short		times_each_must_eat;
	_Atomic short		stop_the_simulation;
}						t_meta_data;

typedef struct s_tab
{
	unsigned short		nb_of_philos;
	pthread_mutex_t		*forks;
	t_philosopher		*philosophers;
	t_node				*thinkers_circle;
}						t_table;

typedef struct s_philo
{
	unsigned short			left_fork_idx;
	unsigned short			right_fork_idx;
	unsigned short			is_right_handed;
	unsigned short			single_philo_at_table;
	unsigned short			id;
	_Atomic t_action		state;
	_Atomic long long		last_meal_time;
	_Atomic unsigned short	nb_of_meals;
	_Atomic unsigned short	is_satisfied;
	_Atomic time_t			start_time;
}						t_philosopher;

_Atomic long long	*get_start_time(void);
t_meta_data			*allocate_meta_data(char **av, int ac);
void				create_the_thinkers(t_meta_data *d);
void				output_state(t_philosopher thinker, long timestamp);
void				free_everything(t_meta_data *data);
t_table				*get_table(void);
t_meta_data			*get_data(void);
void				*philo_thread_callback(void *this_philo);
void				monitor_the_thinkers(void *thinkers);
void				ft_lst_circular(t_node **head);
void				ft_lstcircular_free(t_node **head);
int					ft_atoi(const char *str);
void				ft_lstadd_back(t_node **lst, t_node *nw);
t_node				*ft_lstnew(void *content);
void				philosopher_eat(t_philosopher *philo);
void				philosopher_think(t_philosopher *philo);
void				philosopher_sleep(t_philosopher *philo);
void				philosopher_die(t_philosopher *philo);
void				philosopher_satisfied(t_philosopher *philo);
void				lock_unlock_forks(t_philosopher *philo, int lock_unlock);
void				philo_starves_alone(t_philosopher *philo);
time_t				get_time(void);
time_t				get_time_in_ms(t_philosopher *philo);

#endif

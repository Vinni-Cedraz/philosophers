/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcedraz- <vcedraz-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:33:54 by vcedraz-          #+#    #+#             */
/*   Updated: 2023/09/07 17:40:27 by vcedraz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define TOLERANCE 3
# define TRUE 1
# define FALSE 0
# define CATCH 1
# define PUT_DOWN 0
# define LEFT 0
# define RIGHT 1
# define MAX_NB_OF_PHILOS 200

# define E_MSG \
	"Error: wrong arguments\nUsage: [number of philosopher\
s] [time to die] [time to eat] [time to sleep] and \
optional -> [number of times each philosopher must eat]"

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
	pthread_t			threads[MAX_NB_OF_PHILOS];
	pthread_mutex_t		stdout_mutex;
	time_t				time_to_die;
	t_bool				time_to_eat;
	t_bool				time_to_sleep;
	_Atomic short		times_each_must_eat;
	_Atomic short		stop_the_simulation;
}						t_meta_data;

typedef struct s_tab
{
	t_bool				nb_of_philos;
	pthread_mutex_t		forks[MAX_NB_OF_PHILOS];
	t_node				*thinkers_circle;
}						t_table;

typedef struct s_philo
{
	t_bool				left_fork_idx;
	t_bool				right_fork_idx;
	t_bool				is_right_handed;
	t_bool				single_philo_at_table;
	t_bool				id;
	_Atomic t_action	state;
	_Atomic long long	last_meal_time;
	_Atomic t_bool		nb_of_meals;
	_Atomic t_bool		is_satisfied;
	_Atomic time_t		start_time;
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
void				philosopher_dead(t_philosopher *philo);
void				philosopher_satisfied(t_philosopher *philo);
void				catch_or_put_down_forks(t_philosopher *philo, int catch);
void				philo_starves_alone(t_philosopher *philo);
time_t				get_time(void);
time_t				get_time_in_ms(t_philosopher *philo);
t_bool				am_i_dying(t_philosopher *philo, int eat);

#endif

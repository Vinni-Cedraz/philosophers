/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_the_thinkers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcedraz- <vcedraz-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:45:07 by vcedraz-          #+#    #+#             */
/*   Updated: 2023/09/05 09:12:09 by vcedraz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philosopher		*init_this_thinker(t_philosopher *this_thinker);
static void					*init_circle(t_philosopher *thinkers);

void	create_the_thinkers(t_meta_data *d)
{
	int				i;
	t_philosopher	*thinkers;
	pthread_t		*threads;
	t_philosopher	*this_thinker;

	i = -1;
	thinkers = d->philosophers;
	threads = d->threads;
	while (++i < d->table->nb_of_philos)
	{
		this_thinker = init_this_thinker(&thinkers[i]);
		pthread_create(&threads[i], 0, philo_thread_callback, this_thinker);
	}
	i = -1;
	get_data()->thinkers_circle = init_circle(thinkers);
	monitor_the_thinkers(get_data()->thinkers_circle);
}

static inline t_philosopher	*init_this_thinker(t_philosopher *this_thinker)
{
	static int	call_counter;

	this_thinker->id = call_counter++;
	this_thinker->nb_of_meals = 0;
	this_thinker->state = THINK;
	this_thinker->last_meal_time = get_data()->start_time;
	this_thinker->is_right_handed = this_thinker->id & 1;
	if (get_table()->nb_of_philos == 1)
		this_thinker->is_right_handed = 2;
	this_thinker->left_fork_idx = this_thinker->id - 1;
	if (this_thinker->left_fork_idx == -1)
		this_thinker->left_fork_idx = get_table()->nb_of_philos - 1;
	this_thinker->right_fork_idx = this_thinker->id;
	this_thinker->satisfied = FALSE;
	return (this_thinker);
}

static inline void	*init_circle(t_philosopher *thinkers)
{
	int		i;
	int		nb_of_philos;
	t_node	*linked_list;

	i = -1;
	nb_of_philos = get_table()->nb_of_philos;
	linked_list = NULL;
	while (++i < nb_of_philos)
		ft_lstadd_back(&linked_list, ft_lstnew(&thinkers[i]));
	ft_lst_circular(&linked_list);
	return (linked_list);
}

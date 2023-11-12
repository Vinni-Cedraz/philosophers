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
#include <string.h>

static t_philosopher*init_this_thinker(t_philosopher *this_thinker);
static void			*init_circle(t_philosopher *thinkers);
static void			start_thread_of_each_thinker(t_philosopher *philo);

void	create_the_thinkers(t_meta_data *d)
{
	t_philosopher	*thinkers;
	int				i;

	i = -1;
	thinkers = d->table->philosophers;
	while (++i < d->table->nb_of_philos)
		init_this_thinker(&thinkers[i]);
	start_thread_of_each_thinker(thinkers);
	d->table->thinkers_circle = init_circle(thinkers);
}

static inline t_philosopher	*init_this_thinker(t_philosopher *this_thinker)
{
	static int	call_counter;

	memset(this_thinker, 0, sizeof(*this_thinker));
	this_thinker->id = ++call_counter;
	this_thinker->state = THINK;
	this_thinker->last_meal_time = get_time();
	this_thinker->is_right_handed = this_thinker->id & 1;
	if (get_table()->nb_of_philos == 1)
		this_thinker->single_philo_at_table = TRUE;
	this_thinker->left_fork_idx = this_thinker->id - 1;
	this_thinker->right_fork_idx = this_thinker->id % get_table()->nb_of_philos;
	return (this_thinker);
}

static inline void	start_thread_of_each_thinker(t_philosopher *thinkers)
{
	const t_meta_data		*d = get_data();
	const int				nb_of_philos = get_data()->table->nb_of_philos;
	int						i;

	i = -1;
	while (++i < nb_of_philos)
		pthread_create(&d->threads[i], 0, philo_thread_callback, &thinkers[i]);
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

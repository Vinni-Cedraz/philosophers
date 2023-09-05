/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcedraz- <vcedraz-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:34:53 by vcedraz-          #+#    #+#             */
/*   Updated: 2023/08/31 08:48:13 by vcedraz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_meta_data	*d;
	int			i;

	if (invalid_arg(ac))
		return (1);
	d = allocate_meta_data(av, ac);
	create_the_thinkers(d);
	i = -1;
	while (++i < d->table->nb_of_philos)
		pthread_join(d->threads[i], NULL);
	free_everything(d);
}

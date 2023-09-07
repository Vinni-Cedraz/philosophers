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

static inline unsigned short	invalid_arg(int ac, char **av);
static inline unsigned short	has_negative_nbrs(char **av);
static inline unsigned short	not_a_digit(char **av);
static inline unsigned short	digit(char c);

int	main(int ac, char **av)
{
	t_meta_data	*d;
	int			i;

	if (invalid_arg(ac, av))
		return (1);
	d = allocate_meta_data(av, ac);
	create_the_thinkers(d);
	i = -1;
	while (++i < d->table->nb_of_philos)
		pthread_join(d->threads[i], NULL);
	free_everything(d);
}

static inline unsigned short	invalid_arg(int ac, char **av)
{
	if (ac < 5 || ac > 6 || not_a_digit(av) || has_negative_nbrs(av))
	{
		printf("%s\n", E_MSG);
		return (TRUE);
	}
	return (FALSE);
}

static inline unsigned short	has_negative_nbrs(char **av)
{
	unsigned short	i;
	unsigned short	j;

	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j] != '\0')
		{
			if (av[i][j] == '-')
				return (TRUE);
		}
	}
	return (FALSE);
}

static inline unsigned short	not_a_digit(char **av)
{
	unsigned short	i;
	unsigned short	j;

	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j] != '\0')
		{
			if (!digit(av[i][j]))
				return (TRUE);
		}
	}
	return (FALSE);
}

static inline unsigned short	digit(char c)
{
	return (c <= '9' && c >= '0');
}

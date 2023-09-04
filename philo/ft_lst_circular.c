/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_circular.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcedraz- <vcedraz-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:08:11 by vcedraz-          #+#    #+#             */
/*   Updated: 2023/08/18 15:08:12 by vcedraz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_node			*ft_lstlast(t_node *lst);

t_node	*ft_lstnew(void *content)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(*node));
	node->philosopher = content;
	node->next = NULL;
	return (node);
}

void	ft_lst_circular(t_node **head)
{
	t_node	*tail;

	if (!head || !*head)
		return ;
	tail = *head;
	tail = ft_lstlast(*head);
	tail->next = *head;
}

void	ft_lstcircular_free(t_node **head)
{
	t_node	*current;
	t_node	*temp;

	if (!head || !*head)
		return ;
	current = *head;
	temp = current->next;
	while (temp != *head)
	{
		free(current);
		current = temp;
		temp = temp->next;
	}
	free(current);
	*head = NULL;
}

static inline t_node	*ft_lstlast(t_node *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_node **lst, t_node *nw)
{
	t_node	*temp;

	if (!lst || !nw)
		return ;
	if (!*lst)
	{
		*lst = nw;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = nw;
	nw->next = NULL;
}

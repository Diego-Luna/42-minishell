/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrembla <mtrembla@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 14:58:40 by mtrembla          #+#    #+#             */
/*   Updated: 2022/12/21 13:23:10 by mtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dlist_add_front(t_tokens *l, char *elem)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		exit(0);
	new->content = elem;
	new->next = l->first;
	new->prev = NULL;
	if (l->first)
		l->first->prev = new;
	else
		l->last = new;
	l->first = new;
}

void	dlist_remove_node(t_node *node) 
{
  if (!node->prev && !node->next)
    return;
  else if (!node->prev)
    node->next->prev = NULL;
  else if (!node->next)
    node->prev->next = NULL;
  else
  node->prev->next = node->next;
  node->next->prev = node->prev;
}

void	dlist_free(t_tokens *l)
{
	t_node	*temp;
	t_node	*next;

	next = l->first;
	while (next)
	{
		temp = next;
		next = next->next;
		free(temp);
	}
	l->first = NULL;
	l->last = NULL;
}

void	view(t_tokens l)
{
	t_node	*aff;

	aff = l.first;
	while (aff)
	{
		printf("content:%s\n", aff->content);
		aff = aff->next;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrembla <mtrembla@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 14:58:40 by mtrembla          #+#    #+#             */
/*   Updated: 2023/01/16 13:34:57 by mtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dlist_add_back(t_tokens *l, char *elem)
{
	t_node	*new;
	
	new = malloc(sizeof(t_node));
	if (!new)
		exit(0);
	new->content = elem;
	new->prev = l->last;
	new->next = NULL;
	if (l->last)
		l->last->next = new;
	else
		l->first = new;
	l->last = new;
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
		free(temp->content);
		free(temp);
	}
	l->first = NULL;
	l->last = NULL;
}

void	view(t_tokens l)
{
	t_node	*aff;
	int i = 1;

	aff = l.first;
	while (aff)
	{
		printf("----------------\n");
		printf("token%d:[%s]\n", i++, aff->content);
		aff = aff->next;
	}
}
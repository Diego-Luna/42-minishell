/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:38:41 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/25 12:55:26 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_tokens_size(t_tokens l)
{
	t_node	*aff;
	int		i;

	i = 1;
	aff = l.first;
	while (aff)
	{
		i++;
		aff = aff->next;
	}
	return (i);
}

char	*ft_get_char_node(t_tokens l, int position)
{
	int		i;
	t_node	*aff;

	i = 0;
	aff = l.first;
	while (aff)
	{
		if (position == i)
		{
			return (aff->content);
		}
		i++;
		aff = aff->next;
	}
	return (NULL);
}

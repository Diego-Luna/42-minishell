/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_position_in_token.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:01:29 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/20 13:58:53 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_position_in_token(t_tokens l, char *str, int n_pipe)
{
	int i = 0;
	int pipe = 0;
	t_node	*aff;

	aff = l.first;
	while (aff)
	{
		if (ft_strncmp(aff->content, "|", 2) == 0)
		{
			pipe++;
		}
		else if ( pipe == n_pipe && ft_strncmp(aff->content, str, ft_strlen(aff->content)) == 0)
		{
			return (i);
		}
		i++;
		aff = aff->next;
	}
	return (-1);
}
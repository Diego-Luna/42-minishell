/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_position_in_token.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:01:29 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/26 16:28:35 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_position_in_token(t_tokens l, char *str, int n_pipe, int *start)
{
	t_node	*aff;
	int		pipe;
	int		i;

	pipe = 0;
	i = 0;
	aff = l.first;
	while (aff)
	{
		if (pipe == n_pipe && ft_strncmp(aff->content, str,
				ft_strlen(aff->content)) == 0 && i > *start)
		{
			return (i);
		}
		else if (ft_strncmp(aff->content, "|\0", 2) == 0)
		{
			pipe++;
		}
		i++;
		aff = aff->next;
	}
	return (-1);
}

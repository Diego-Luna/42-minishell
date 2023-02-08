/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:59:49 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/02/08 12:05:19 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_check_multiples_pipes(t_state *state)
{
	int		status;
	t_node	*aff;

	aff = state->tokens->first;
	status = 0;
	while (aff)
	{
		if (status == 1 && ft_strncmp(aff->content, "|", 1) == 0)
		{
			ft_error_message(M_ERROR_TOKENS, NULL, state, N_ERROR_TOKENS);
			return ;
		}
		if (ft_strncmp(aff->content, "||\0", 3) == 0)
		{
			status = 1;
		}
		else
		{
			status = 0;
		}
		aff = aff->next;
	}
}

void	ft_check_pipes(t_state *state)
{
	int		i;
	t_node	*aff;

	aff = state->tokens->first;
	i = 0;
	while (aff)
	{
		if (aff->content && ft_strncmp(aff->content, "||\0", 3) == 0 && i == 0)
		{
			ft_error_message(M_ERROR_TOKENS, NULL, state, N_ERROR_TOKENS);
			return ;
		}
		aff = aff->next;
		i++;
	}
	ft_check_multiples_pipes(state);
}

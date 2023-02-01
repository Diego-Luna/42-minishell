/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_command_array_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:26:04 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/02/01 13:46:00 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_save_type_redirection_while(t_state *state, t_node *aff, int i)
{
	int		ii;
	t_cmd	*cmd;

	ii = 3;
	cmd = &state->cmds[i];
	while (ii >= 0)
	{
		if (ft_strncmp(aff->content, state->t_redirection[ii],
				ft_strlen(state->t_redirection[ii])) == 0)
		{
			state->cmds[i].redirect[cmd->i_redi] = ii;
			cmd->i_redi++;
			return (1);
		}
		ii--;
	}
	return (0);
}

int	ft_save_type_redirection(t_state *state, int i)
{
	t_node	*aff;
	int		ii;
	int		pipe;

	aff = state->tokens->first;
	pipe = 0;
	ii = 0;
	while (aff)
	{
		if (aff->content)
		{
			if (pipe == i)
				ii = ft_save_type_redirection_while(state, aff, i);
			else if (ft_strncmp(aff->content, "|\0", 2) == 0)
				pipe++;
		}
		aff = aff->next;
	}
	return (0);
}

char	**ft_table_token(t_state *state)
{
	int		i;
	char	**table;

	i = 0;
	table = ft_calloc(sizeof(char *), state->cmd_nmbs + 1);
	while (i < state->cmd_nmbs)
	{
		table[i] = ft_save_token(state, i);
		i++;
	}
	return (table);
}

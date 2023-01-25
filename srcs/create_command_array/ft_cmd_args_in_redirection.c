/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_args_in_redirection.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:55:08 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/25 13:55:22 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_cmd_args_in_redirection_create(t_state *state, int i, t_cmd *cmd,
		int size_copy)
{
	int		position_redi;
	char	**new;
	int		ii;
	int		iii;

	ii = 0;
	iii = 0;
	position_redi = 0;
	new = ft_calloc(sizeof(char *), size_copy + 1);
	while (ii < size_copy)
	{
		if (ft_strncmp(state->t_redirection[cmd->redirect], cmd->cmd_args[ii],
				ft_strlen(cmd->cmd_args[ii])) == 0)
		{
			position_redi = 1;
			ii++;
		}
		else
		{
			new[iii] = ft_strdup(state->cmds[i].cmd_args[ii]);
			iii++;
		}
		ii++;
	}
	return (new);
}

void	ft_cmd_args_in_redirection(t_state *state, int i)
{
	t_cmd	*cmd;
	char	**new;
	int		size_copy;
	int		position_redi;

	cmd = &state->cmds[i];
	state->cmds[i].t_redirection = ft_calloc(sizeof(char *), 2);
	position_redi = ft_position_in_token(*state->tokens,
			state->t_redirection[cmd->redirect], i);
	if (position_redi >= ft_tokens_size(*state->tokens) - 2)
	{
		state->cmds[i].cmd_args = NULL;
		ft_error_message(M_ERROR_TOKENS_REDE, NULL, state, N_ERROR_TOKENS_REDE);
		return ;
	}
	position_redi++;
	state->cmds[i].t_redirection[0] = ft_strdup(ft_get_char_node(*state->tokens,
				position_redi));
	state->cmds[i].cmd_args = ft_content_tokens(state, i, *state->tokens);
	size_copy = ft_size_table(state->cmds[i].cmd_args);
	new = ft_cmd_args_in_redirection_create(state, i, cmd, size_copy);
	state->cmds[i].cmd_args = (char **)ft_free_table(state->cmds[i].cmd_args);
	state->cmds[i].cmd_args = new;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_args_in_redirection.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:55:08 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/26 17:10:05 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_cmd_args_in_redirection_create(t_state *state, char **tem , t_cmd *cmd,
		int size_copy)
{
	int		position_redi;
	char	**new;
	int		ii;
	int		iii;

	ii = 0;
	iii = 0;
	position_redi = 0;
	new = ft_calloc(sizeof(char *), size_copy);
	cmd->i_redi = 0;
	while (ii < size_copy)
	{
		if (ft_strncmp(state->t_redirection[cmd->redirect[cmd->i_redi]], tem[ii],
				ft_strlen(tem[ii])) == 0)
		{
			position_redi = 1;
			cmd->i_redi++;
			ii++;
		}
		else if (ii < size_copy)
		{
			new[iii] = ft_strdup(tem[ii]);
			iii++;
		}
		ii++;
	}
	return (new);
}

void ft_cmd_args_in_red_divi(t_state *state, int i, int *start)
{
	int		position_redi;
	t_cmd	*cmd;

	cmd = &state->cmds[i];
	position_redi = ft_position_in_token(*state->tokens,
			state->t_redirection[cmd->redirect[cmd->i_redi]], i, start);
	*start = position_redi;
	if (position_redi >= ft_tokens_size(*state->tokens) - 2)
	{
		state->cmds[i].cmd_args = NULL;
		ft_error_message(M_ERROR_TOKENS_REDE, NULL, state, N_ERROR_TOKENS_REDE);
		return ;
	}
	position_redi++;
	state->cmds[i].t_redirection[cmd->i_redi] = ft_strdup(ft_get_char_node(*state->tokens,
				position_redi));
}

void	ft_cmd_args_in_redirection(t_state *state, int i)
{
	t_cmd	*cmd;
	char	**new;
	char	**tem;
	int		size_copy;

	cmd = &state->cmds[i];
	state->cmds[i].t_redirection = ft_calloc(sizeof(char *), cmd->n_of_redi);
	cmd->i_redi = 0;
	size_copy = -1;
	while ( cmd->i_redi < cmd->n_of_redi - 1)
	{
		ft_cmd_args_in_red_divi(state, i, &size_copy);
		cmd->i_redi++;
	}
	tem = ft_content_tokens(state, i, *state->tokens);
	size_copy = ft_size_table(tem);
	new = ft_cmd_args_in_redirection_create(state, tem, cmd, size_copy);
	ft_free_table(tem);
	state->cmds[i].cmd_args = new;
}

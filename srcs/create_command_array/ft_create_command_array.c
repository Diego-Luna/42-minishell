/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_command_array.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:35:55 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/24 19:12:40 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_save_type_redirection(t_state *state, int i)
{
	t_node	*aff;
	int ii;
	int pipe;

	aff = state->tokens->first;
	pipe = 0;
	while (aff)
	{
		if (aff->content)
		{
			if (pipe == i)
			{
				ii = 3;
				while (ii >= 0)
				{
					if (ft_strncmp(aff->content, state->t_redirection[ii], ft_strlen(state->t_redirection[ii])) == 0)
					{
						state->cmds[i].redirect = ii;
						return;
					}
					ii--;
				}
			}else if (ft_strncmp(aff->content, "|\0", 2) == 0)
			{
				pipe++;
			}
		}
		aff = aff->next;
	}
}

char **ft_table_token(t_state *state)
{
	int i = 0;
	char **table;

	table = ft_calloc(sizeof(char *),  state->cmd_nmbs + 1);
	while (i < state->cmd_nmbs)
	{
		table[i] = ft_save_token(state, i);
		i++;
	}

	return (table);
}

void ft_create_t_redirection(t_state *state)
{
	state->t_redirection = ft_calloc(sizeof(char *), 5);
	state->t_redirection[0] =  ft_strdup("<");
	state->t_redirection[1] =  ft_strdup(">");
	state->t_redirection[2] =  ft_strdup("<<");
	state->t_redirection[3] =  ft_strdup(">>");
	state->t_redirection[4] =  0;
}

// It is in charge of creating the array of the commanded functions
void ft_create_command_array(t_state *state)
{
	int i = 0;

	ft_create_t_redirection(state);
	state->cmds = ft_calloc(sizeof(t_cmd), state->cmd_nmbs + 1);
	state->t_comands = ft_table_token(state);
	while (i < state->cmd_nmbs)
	{
		state->cmds[i].id = i;
		state->cmds[i].redirect = -1;
		state->cmds[i].file = -1;
		ft_save_type_redirection(state, i);
		if (state->cmds[i].redirect >= 0)
		{
			ft_cmd_args_in_redirection(state, i);
		}
		else
		{
			state->cmds[i].t_redirection = ft_calloc(sizeof(char *), 1);
			state->cmds[i].cmd_args = ft_content_tokens(state, i, *state->tokens);
		}
		i++;
	}
}
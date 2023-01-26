/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_command_array.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:35:55 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/26 17:10:34 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_save_type_redirection_while(t_state *state, t_node *aff, int i)
{
	int	ii;
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

int	ft_is_redi(t_state *state, t_node *aff)
{
	int	ii;

	ii = 3;
	while (ii >= 0)
	{
		if (ft_strncmp(aff->content, state->t_redirection[ii],
				ft_strlen(state->t_redirection[ii])) == 0)
		{
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

void	ft_create_t_redirection(t_state *state)
{
	state->t_redirection = ft_calloc(sizeof(char *), 5);
	state->t_redirection[0] = ft_strdup("<");
	state->t_redirection[1] = ft_strdup(">");
	state->t_redirection[2] = ft_strdup("<<");
	state->t_redirection[3] = ft_strdup(">>");
	state->t_redirection[4] = 0;
}

int ft_number_of_redirection(t_state *state, t_node	*aff, int number_pipe)
{
	int number;
	int pipe;
	int ii;

	number = 0;
	pipe = 0;
	ii = 0;
	while (aff)
	{
		if (aff->content)
		{
			if (pipe == number_pipe && ft_is_redi(state, aff) == 1)
			{
				number++;
			}
			else if (ft_strncmp(aff->content, "|\0", 2) == 0)
			{
				pipe++;
			}
		}
		aff = aff->next;
	}
	return (number);
}

void ft_crate_array(t_state *state, t_cmd *cmd, int num_comand)
{
	t_node	*aff;
	int num;
	int i;

	(void)num;
	i = 0;
	aff = state->tokens->first;
	cmd->n_of_redi = 0;
	cmd->n_of_redi = ft_number_of_redirection(state, aff, num_comand);
	cmd->n_of_redi++;
	cmd->redirect = ft_calloc(sizeof(int), cmd->n_of_redi);
	cmd->i_redi = 0;
	while (i < cmd->n_of_redi)
	{
		cmd->redirect[i] = -2;
		i++;
	}
	cmd->redirect[0] = -1;
}

// It is in charge of creating the array of the commanded functions
void	ft_create_command_array(t_state *state)
{
	int	i;

	i = 0;
	ft_create_t_redirection(state);
	state->cmds = ft_calloc(sizeof(t_cmd), state->cmd_nmbs);
	state->t_comands = ft_table_token(state);
	while (i < state->cmd_nmbs)
	{
		state->cmds[i].id = i;
		state->cmds[i].file = -1;
		ft_crate_array(state, &state->cmds[i], i);
		ft_save_type_redirection(state, i);
		if (state->cmds[i].redirect[0] >= 0)
		{
			// printf("\n 🏁 \n");
			ft_cmd_args_in_redirection(state, i);
			// ft_print_table_debug(state->cmds[i].cmd_args);
		}
		else
		{
			// printf("\n 🔥 \n");
			state->cmds[i].t_redirection = ft_calloc(sizeof(char *), 1);
			state->cmds[i].cmd_args = ft_content_tokens(state, i,
					*state->tokens);
		}
		i++;
	}
}

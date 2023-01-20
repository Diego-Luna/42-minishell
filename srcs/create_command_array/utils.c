/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:38:41 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/20 13:58:56 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_tokens_size(t_tokens l)
{
	t_node	*aff;
	int i = 1;

	aff = l.first;
	while (aff)
	{
		i++;
		aff = aff->next;
	}
	return (i);
}

char *ft_get_char_node(t_tokens l, int position)
{
	int i;
	t_node	*aff;

	i = 0;
	aff = l.first;
	while (aff)
	{
		if ( position == i)
		{
			return (aff->content);
		}
		i++;
		aff = aff->next;
	}
	return (NULL);
}

char *ft_save_token(t_state *state, int number_pipe)
{
	char *save;
	t_node	*aff;
	int i = 0;
	int pipe = 0;
	int size = 0;

	aff = state->tokens->first;
	if (state->cmd_nmbs == 1)
	{
		while (aff)
		{
			i++;
			size += ft_strlen(aff->content) + 1;
			aff = aff->next;
		}
	}
	else
	{
		while (aff)
		{
			if (ft_strncmp(aff->content, "|\0", 2) == 0)
			{
				pipe++;
			}
			else if (pipe > number_pipe)
			{
				break;
			}
			else if (pipe == number_pipe)
			{
				size += ft_strlen(aff->content);
				i++;
				if (aff->next && ft_strncmp(aff->next->content, "|\0", 2) != 0)
				{
					size++;
				}
			}
			aff = aff->next;
		}
	}
	size++;
	save = ft_calloc(sizeof(char), size);
	aff = state->tokens->first;
	i = 0;
	pipe = 0;
	if (state->cmd_nmbs == 1)
	{
		while (aff)
		{
			ft_strlcat(save, aff->content, size + 1);
			aff = aff->next;
			if (aff)
			{
				ft_strlcat(save, " ", size + 1);
			}
		}
	}
	else
	{
		while (aff)
		{
			if (ft_strncmp(aff->content, "|\0", 2) == 0)
			{
				pipe++;
			}
			else if (pipe > number_pipe)
			{
				break;
			}
			else if (pipe == number_pipe)
			{
				ft_strlcat(save, aff->content, size);
				// ft_strlcat(save, aff->content, size + 1);
				i++;
				if (aff->next)
				{
					ft_strlcat(save, " ", 1);
				}
			}
			aff = aff->next;
		}
	}
	return (save);
}

char **ft_content_tokens(t_state *state, int number_pipe, t_tokens l)
{
	char **table;
	t_node	*aff;
	int i = 0;
	int pipe = 0;

	aff = l.first;
	if (state->cmd_nmbs == 1)
	{
		while (aff)
		{
			i++;
			aff = aff->next;
		}
	}
	else
	{
		while (aff)
		{
			if (ft_strncmp(aff->content, "|\0", 2) == 0)
			{
				pipe++;
			}
			else if (pipe > number_pipe)
			{
				break;
			}
			else if (pipe == number_pipe)
			{
				i++;
			}
			aff = aff->next;
		}
	}
	table = ft_calloc(sizeof(char *), i + 1);
	aff = l.first;
	pipe = 0;
	i = 0;
	if (state->cmd_nmbs == 1 )
	{
		while (aff)
		{
			table[i] = ft_strdup(aff->content);
			aff = aff->next;
			i++;
		}
	}
	else
	{
		while (aff)
		{
			if (ft_strncmp(aff->content, "|\0", 2) == 0)
			{
				pipe++;
			}
			else if (pipe > number_pipe)
			{
				break;
			}
			else if (pipe == number_pipe)
			{
				table[i] = ft_strdup(aff->content);
				i++;
			}
			aff = aff->next;
		}
	}
	return (table);
}

void	ft_cmd_args_in_redirection(t_state *state, int i)
{
	int ii = 0;
	int iii = 0;
	int position_redi = 0;
	int	size_copy = 0;
	char	**new;
	t_cmd *cmd;

	state->cmds[i].t_redirection = ft_calloc(sizeof(char *), 2);
	cmd = &state->cmds[i];
	position_redi = ft_position_in_token(*state->tokens, state->t_redirection[cmd->redirect], i);
	if (position_redi >= ft_tokens_size(*state->tokens) - 2)
	{
		state->cmds[i].cmd_args = NULL;
		ft_error_message(M_ERROR_TOKENS_REDE, NULL, state, N_ERROR_TOKENS_REDE);
		return;
	}
	position_redi++;
	state->cmds[i].t_redirection[0] = ft_strdup(ft_get_char_node(*state->tokens, position_redi));
	state->cmds[i].cmd_args = ft_content_tokens(state, i, *state->tokens);
	size_copy = ft_size_table(state->cmds[i].cmd_args);
	new = ft_calloc( sizeof(char *), size_copy);
	position_redi = 0;
	while (ii < size_copy)
	{
		if (ft_strncmp(state->t_redirection[cmd->redirect], state->cmds[i].cmd_args[ii], ft_strlen(state->cmds[i].cmd_args[ii])) == 0)
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
	state->cmds[i].cmd_args = (char **)ft_free_table(state->cmds[i].cmd_args);
	state->cmds[i].cmd_args = new;
}
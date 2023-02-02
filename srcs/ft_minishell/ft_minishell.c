/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:15:00 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/02/01 19:08:11 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// It shows us the error, at the same time that it helps us to debug.
void	ft_error_message(char *str, char **table, t_state *state, int error)
{
	int	i;

	i = 0;
	// if (state->debug == 1)
	// {
		// printf("Error number:%d ", error);
	// }
	// printf("%s", str);
	ft_putstr_fd(str, 2);
	while (table && table[i])
	{
		// printf(" %s", table[i]);
		ft_putstr_fd(table[i], 2);
		i++;
	}
	// printf("\n");
	ft_putstr_fd("\n", 2);
	state->error = error;
}

// A function that allows us to run the next part
// of the code as long as there are no errors.
void	ft_run_when_is_no_error(t_state *state, void (*f)(t_state *state))
{
	if (state->error == NO_ERROR)
	{
		f(state);
	}
	else
	{
		return ;
	}
}

int	ft_number_comands_parsing(t_tokens tokens)
{
	t_node	*aff;
	int		i;

	i = 1;
	aff = tokens.first;
	while (aff)
	{
		if (ft_strncmp(aff->content, "|\0", 2) == 0 || ft_strncmp(aff->content, "||\0", 2) == 0)
		{
			i++;
		}
		aff = aff->next;
	}
	return (i);
}

void ft_check_pipes(t_state *state)
{
	int status;
	t_node	*aff;

	aff = state->tokens->first;
	status = 0;
	while (aff)
	{
		if (aff->content && ft_strncmp(aff->content, "|\0", 2) == 0)
		{
			if (status == 1)
			{
				ft_error_message(M_ERROR_TOKEN, NULL, state, N_ERROR_TOKEN);
				return;
			}
			status = 1;
		}else
			status = 0;
		aff = aff->next;
	}
	aff = state->tokens->first;
	status = 0;
	while (aff)
	{
		if (status == 1 && ft_strncmp(aff->content, "|", 1) == 0)
		{
			ft_error_message(M_ERROR_TOKEN, NULL, state, N_ERROR_TOKEN);
			return;
		}
		if (ft_strncmp(aff->content, "||\0", 3) == 0)
		{
			status = 1;
		}else
		{
			status = 0;
		}
		aff = aff->next;
	}
}

//  We check the number of commands sent and create our array,
// 	with the information of each one
void	ft_minishell(t_state *state, char *line, t_tokens *tokens)
{
	state->cmd_nmbs = ft_number_comands_parsing(*tokens);
	state->line = line;
	if (state->cmd_nmbs > 0 && state->error == NO_ERROR)
	{
		state->tokens = NULL;
		state->tokens = tokens;
		ft_run_when_is_no_error(state, ft_check_pipes);
		ft_run_when_is_no_error(state, ft_create_command_array);
		// ft_print_cmds(state);
		ft_run_when_is_no_error(state, ft_add_info_comands);
		ft_run_when_is_no_error(state, ft_run_comands);
		ft_handle_error_pipe(state);
		ft_check_exit(state);
	}
}

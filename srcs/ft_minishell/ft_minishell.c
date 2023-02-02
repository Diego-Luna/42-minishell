/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:15:00 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/02/02 11:59:56 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// It shows us the error, at the same time that it helps us to debug.
void	ft_error_message(char *str, char **table, t_state *state, int error)
{
	int	i;

	i = 0;
	ft_putstr_fd(str, 2);
	while (table && table[i])
	{
		ft_putstr_fd(table[i], 2);
		i++;
	}
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
		if (ft_strncmp(aff->content, "|\0", 2) == 0 || ft_strncmp(aff->content,
				"||\0", 2) == 0)
		{
			i++;
		}
		aff = aff->next;
	}
	return (i);
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
		ft_run_when_is_no_error(state, ft_add_info_comands);
		ft_run_when_is_no_error(state, ft_run_comands);
		ft_handle_error_pipe(state);
		ft_check_exit(state);
	}
}

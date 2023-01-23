/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrembla <mtrembla@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:15:00 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/23 12:41:41 by mtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Function for debug, which shows us all the created commands and their
	information. */
void ft_print_cmds(t_state *state)
{
	int i = 0 ;
	int ii = 0;
	int iii = 0;

	ft_printf("\n ft_print_cmds \n");
	while (state->cmd_nmbs && i < state->cmd_nmbs)
	{
		ft_printf("id{%i} cmd{%s} ", state->cmds[i].id, state->cmds[i].cmd);
		ii = 0;
		// while (state->cmds[i].cmd_args && ii < state->cmd_nmbs && state->cmds[i].cmd_args[ii])
		while (state->cmds[i].cmd_args && state->cmds[i].cmd_args[ii])
		{
			ft_printf("cmd_args{%s} ", state->cmds[i].cmd_args[ii]);
			ii++;
		}
		iii = 0;
		while (state->cmds[i].t_redirection && state->cmds[i].t_redirection[iii])
		{
			ft_printf("t_redirection{%s} ", state->cmds[i].t_redirection[iii]);
			iii++;
		}
		
		ft_printf("\n");
		i++;
	}
}


// It shows us the error, at the same time that it helps us to debug.
void ft_error_message(char *str, char **table, t_state *state, int error)
{
	int i = 0;

	if (state->debug == 1)
	{
		printf("Error number:%d ", error);
	}
	printf("%s", str);
	while (table && table[i])
	{
		printf(" %s", table[i]);
		i++;
	}
	printf("\n");
	state->error = error;
}

// A function that allows us to run the next part of the code as long as there are no errors.
void	ft_run_when_is_no_error(t_state *state, void (*f)(t_state *state))
{
	if (state->error == NO_ERROR)
	{
		f(state);
	}else{
		return ;
	}
}


int ft_number_comands_parsing(t_tokens tokens)
{
	t_node	*aff;
	int i = 1;

	aff = tokens.first;
	while (aff)
	{
		if (ft_strncmp(aff->content, "|\0", 2) == 0)
		{
			i++;
		}
		aff = aff->next;
	}
	return (i);
}

// We check the number of commands sent and create our array, with the information of each one
void	ft_minishell(t_state	*state, char *line, t_tokens *tokens)
{
	state->cmd_nmbs = ft_number_comands_parsing(*tokens);
	state->line = line;
	if (state->cmd_nmbs > 0 && state->error == NO_ERROR)
	{
		state->tokens = NULL;
		state->tokens = tokens;
		// ft_signal_stop();
		ft_run_when_is_no_error(state, ft_create_command_array);
		ft_run_when_is_no_error(state, ft_add_info_comands);
		ft_run_when_is_no_error(state, ft_run_comands);
		ft_handle_error_pipe(state);
		ft_check_exit(state);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_comands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:49:30 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/25 15:31:39 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_wait_childs(t_state	*state)
{
	state->index = 0;
	while (state->index < state->cmd_nmbs)
	{
		waitpid(state->pid[state->index], &state->fork_error, 0);
		state->index++;
	}
	ft_signals();
}

// Functions to run more than one, command with pipes.
void	ft_process_comands(t_state	*state)
{
	state->pid = ft_calloc(sizeof(pid_t), state->cmd_nmbs);
	if (!state->pid)
	{
		ft_error_message(M_ERROR_CREATE_PIPE, NULL, state, N_ERROR_CREATE_PIPE);
	}
	state->index = 0;
	ft_run_when_is_no_error(state, ft_run_childs);
	ft_run_when_is_no_error(state, ft_wait_childs);
	ft_free(state->pid);
}

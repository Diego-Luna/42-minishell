/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_comands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:49:30 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/20 13:59:09 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// The equation of the children commands with the fork
void	ft_run_childs(t_state *state)
{
	int error;

	error = 0;
	state->index = 0;
	while (state->index < state->cmd_nmbs && state->error == 0)
	{
		int		fd[2];

		pipe(fd);
		state->pid[state->index] = fork();
		if (state->pid[state->index] == 0)
		{
			ft_fork_signal();
			if (state->index < state->cmd_nmbs - 1)
			{
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
			}
			ft_on_redirection(state);
			if (ft_run_comand_build(state) == 0)
			{
				error = ft_execve(state);
				ft_error_message(M_ERROR_EXECVE_PIPES, state->cmds[state->index].cmd_args, state, N_ERROR_EXECVE_PIPES);
			}
			ft_close_fd();
			exit(error);
		}
		else if (state->index < state->cmd_nmbs)
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
		}
		state->index++;
	}
}

void ft_wait_childs(t_state	*state)
{
	state->index = 0;
	while (state->index < state->cmd_nmbs)
	{
		waitpid(state->pid[state->index], &state->fork_error, 0);
		state->index++;
	}
}

// Functions to run more than one, command with pipes.
void ft_process_comands(t_state	*state)
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
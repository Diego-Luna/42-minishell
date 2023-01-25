/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_comand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:48:56 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/25 15:22:15 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Command process with flork, for a single command,
// the child process executes the command and the parent waits until 
// it has finished.
void	ft_process_comand_fork(t_state *state)
{
	int		error;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_fork_signal();
		error = ft_execve(state);
		ft_error_message(M_ERROR_EXECVE, state->cmds[0].cmd_args, state,
			N_ERROR_EXECVE);
		exit(errno);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &state->fork_error, 0);
	}
	ft_signals();
}

// This function creates a child process where the command sent
// will be executed.
void	ft_process_comand(t_state *state)
{
	state->index = 0;
	if (state->stop != STOP)
	{
		ft_on_redirection(state);
		if (ft_run_comand_build(state) == 0)
		{
			ft_run_when_is_no_error(state, ft_process_comand_fork);
		}
	}
}

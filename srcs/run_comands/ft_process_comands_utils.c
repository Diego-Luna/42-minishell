/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_comands_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:31:04 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/30 17:04:53 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_run_childs_utils_execve(t_state *state)
{
	int		error;

	error = ft_execve(state);
	ft_error_message(M_ERROR_EXECVE_PIPES, state->cmds[state->index].cmd_args,
		state, N_ERROR_EXECVE_PIPES);
	ft_close_fd();
	exit(errno);
}

void	ft_run_childs_utils_run(t_state *state, int *fd)
{
	int		error;

	error = 1;
	if (state->index < state->cmd_nmbs - 1)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
	}
	ft_on_redirection(state);
	if (ft_run_comand_build(state) == 0)
	{
		ft_run_childs_utils_execve(state);
	}
	ft_close_fd();
	exit(error);
}

void	ft_run_childs_utils(t_state *state)
{
	int		fd[2];

	ft_fork_signal();
	pipe(fd);
	state->pid[state->index] = fork();
	if (state->pid[state->index] == 0)
		ft_run_childs_utils_run(state, fd);
	else if (state->index < state->cmd_nmbs)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
	else
		signal(SIGINT, SIG_IGN);
}

// The equation of the children commands with the fork
void	ft_run_childs(t_state *state)
{
	state->index = 0;
	while (state->index < state->cmd_nmbs && state->error == 0)
	{
		ft_run_childs_utils(state);
		state->index++;
	}
}

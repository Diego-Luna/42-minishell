/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:58:18 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/27 17:56:33 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_execve_direccion(t_state *state, int i)
{
	int	error;

	ft_close_fd();
	error = execve(state->cmds[i].cmd_args[0], state->cmds[i].cmd_args,
			state->g_env);
	return (error);
}

void	ft_execve_no_path(t_state *state)
{
	char	**erro_path;

	erro_path = ft_calloc(sizeof(char *), 2);
	erro_path[0] = ft_strdup("PATH");
	ft_error_message(M_ERROR_FIND_ENV, erro_path, state, N_ERROR_FIND_ENV);
	ft_free_table(erro_path);
	ft_close_fd();
	exit(errno);
}

void	ft_execve_get_path(t_state *state, int i)
{
	state->env_path = ft_find_env(state->g_env, "PATH=");
	state->cmd_paths = ft_split(state->env_path, ':');
	state->cmds[i].cmd = ft_get_comand_p(state->cmd_paths,
			state->cmds[i].cmd_args[0]);
}

// Our own execve
int	ft_execve(t_state *state)
{
	int	error;
	int	i;

	i = state->index;
	if (access(state->cmds[i].cmd_args[0], X_OK | F_OK) != -1)
		return (ft_execve_direccion(state, i));
	if (ft_find_env(state->g_env, "PATH=") == NULL)
		ft_execve_no_path(state);
	ft_execve_get_path(state, i);
	if (!state->cmds[i].cmd)
	{
		ft_error_message(M_ERROR_PATH, state->cmds[i].cmd_args, state,
			N_ERROR_PATH);
		ft_close_fd();
		exit(errno);
	}
	ft_close_fd();
	error = execve(state->cmds[i].cmd, state->cmds[i].cmd_args, state->g_env);
	return (error);
}

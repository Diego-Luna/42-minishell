/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:58:19 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/19 12:58:27 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// We create the necessary space to create our genv, and with the option of making the old version free.
char	**ft_crate_env(char **old, int size, int f)
{
	char	**new;
	int		i;

	if (old == NULL)
	{
		return (NULL);
	}
	new = ft_calloc(sizeof(char *), (ft_size_table(old) + size));
	if (!new)
		return (NULL);
	i = 0;
	while (old[i])
	{
		new[i] = ft_strdup(old[i]);
		i++;
	}
	if (f > 0)
	{
		ft_free_table(old);
	}
	return (new);
}

// We start the state variables, and those that need mesh, start with NULL
void	ft_init_state(t_state	*state, char **envp)
{
	state->g_env = NULL;
	state->g_env = ft_crate_env(envp, 1, -1);
	state->t_comands = NULL;
	state->env_path = NULL;
	state->cmd_paths = NULL;
	state->cmds = NULL;
	state->pid = NULL;
	state->cmd_nmbs = 0;
	state->index = 0;
	state->stop = NO_ERROR;
	state->fork_error = NO_ERROR;
	state->save_stdout = 0;
	state->save_stdin = 0;
	state->error = NO_ERROR;
	state->debug = 1;
	state->pipe_stop = -1;
	ft_handle_error_pipe(state);
}
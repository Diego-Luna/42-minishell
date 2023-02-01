/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:58:19 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/31 18:56:42 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// We create the necessary space to create our genv,
// and with the option of making the old version free.
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

void	ft_increment_shelllevel(t_state *state)
{
	char	**past;
	char	*str_num;
	int		num;

	if (ft_find_env(state->g_env, "SHLVL=") != NULL
		&& ft_strlen(ft_find_env(state->g_env, "SHLVL=")) > 0)
	{
		num = ft_atoi(ft_find_env(state->g_env, "SHLVL="));
		num++;
		str_num = ft_itoa(num);
		past = ft_calloc(sizeof(char *), 3);
		past[0] = ft_strdup("1");
		past[1] = ft_strjoin("SHLVL=", str_num);
		ft_add_env(state, past, 1);
		ft_free_table(past);
		ft_free(str_num);
	}
}

// We start the state variables, and those that need mesh, start with NULL
void	ft_init_state(t_state *state, char **envp)
{
	state->g_env = NULL;
	state->g_env = ft_crate_env(envp, 1, -1);
	state->t_comands = NULL;
	state->t_redirection = NULL;
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
	state->exit = -1;
	ft_handle_error_pipe(state);
	ft_increment_shelllevel(state);
}

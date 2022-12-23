/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:50:01 by dluna-lo          #+#    #+#             */
/*   Updated: 2022/12/22 20:03:17 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**g_env;

// returns the size of an array
int	ft_size_table(char **array, int add)
{
	int	i;

	i = 0;
	while (array[i])
	{
		i++;
	}
	return (i + add);
}

// we make free, and we put at the end a null. 
void	*ft_free(void *ptr)
{
	if (ptr)
	{
		free(ptr);
	}
	return (NULL);
}

// We free a table
void	**ft_free_table(char **array)
{
	int	i;

	if (!array)
	{
		return (NULL);
	}
	i = -1;
	while (array[++i])
	{
		if (array[i])
		{
			array[i] = ft_free(array[i]);
		}
	}
	array = ft_free(array);
	return (NULL);
}


char	**ft_crate_env(char **old, int size, int f)
{
	char	**new;
	int		i;

	if (old == NULL)
	{
		return (NULL);
	}
	new = ft_calloc(sizeof(char *), (ft_size_table(old, 1) + size));
	if (!new)
		return (NULL);
	i = -1;
	while (old[++i])
		new[i] = ft_strdup(old[i]);
	if (f == 1)
		ft_free_table(old);
	return (new);
}

void	ft_init_state(t_state	*state, char **envp)
{
	state->i_run_pipes = 0;
	if (g_env == NULL)
	{
		g_env = ft_crate_env(envp, 0, 0);
	}
	state->t_comands = NULL;
	state->env_path = NULL;
	state->cmd_paths = NULL;
	state->pipe = NULL;
	state->cmds = NULL;
	state->cmd_nmbs = 0;
	state->pipe_nmbs = 0;
	state->index = 0;
	state->stop = NO_ERROR;
	state->fork_error = NO_ERROR;
	state->save_stdout = 0;
	state->save_stdin = 0;
	state->i_run_pipes = 0;
	state->error = NO_ERROR;
	state->debug = 1;
}

int	main(int argc, char **argv, char **envp)
{
	t_state	state;
	int i = 0;

	(void)argc;
	(void)argv;
	char *line;

	g_env = NULL;
	ft_init_state(&state, envp);
	ft_signals();
	while (i < 3)
	{
    	line = readline("minishell$> ");
		if (!line)
			break;
		if (line && *line)
		{
			add_history(line);
			state.error = 0 ;
			ft_minishell(&state, line);
		}
		free(line);
		i++;
	}
    return (0);
}

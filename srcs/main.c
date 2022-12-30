/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:50:01 by dluna-lo          #+#    #+#             */
/*   Updated: 2022/12/30 17:32:27 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// extern char	**g_env;
char	**g_env;

// returns the size of an array
int	ft_size_table(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		i++;
	}
	return (i);
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

// falta
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
	if (f < 0)
	{
		while (old[i])
		{
			new[i] = ft_strdup(old[i]);
			i++;
		}
	}else
	{
		while (old[i])
		{
			if ( i != f)
			{
				new[i] = ft_strdup(old[i]);
			}
			i++;
		}
	}
	if (f > 0)
	{
		ft_free_table(old);
	}
	return (new);
}

// falta
void	ft_init_state(t_state	*state, char **envp)
{
	if (g_env == NULL)
	{
		g_env = ft_crate_env(envp, 1, -1);
	}
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
}

int	main(int argc, char **argv, char **envp)
{
	t_state	state;

	(void)argc;
	(void)argv;
	char *line;

	g_env = NULL;
	ft_init_state(&state, envp);
	ft_signals();
	while (state.stop != STOP)
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
	}
    return (0);
}

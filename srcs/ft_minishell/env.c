/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:56:24 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/20 16:56:47 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// This function is in charge of finding the PATH variable, and returning its value, if there is an error it puts it in the global variable
char	*ft_find_env(char **envp, char *path)
{
	int	i;
	int	ii;
	int	size;

	i = 0;
	size = ft_size_table(envp);
	ii = ft_strlen(path);
	while (i < size && ft_strncmp(path, envp[i], ii))
	{
		i++;
	}
	if (i == size)
	{
		return (NULL);
	}
	// return (envp[i] + 5);
	return (envp[i] + ii);
}

int	ft_find_env_index(char **envp, char *path)
{
	int	i;
	int	size;

	i = 0;
	size = ft_size_table(envp);
	while (i < size && ft_strncmp(path, envp[i], ft_strlen(path)))
	{
		i++;
	}
	if (i == size)
	{
		return (-1);
	}
	return (i);
}

// look in a char table and return the position of it
int ft_find_env_position(char **envp, char *path)
{
	int	i;
	int	ii;
	int	size;

	i = 0;
	size = ft_size_table(envp);
	ii = ft_strlen(path);
	while (i < size && ft_strncmp(path, envp[i], ii))
	{
		i++;
	}
	if (i == size)
	{
		return (-1);
	}
	return (i);
}

int ft_delate_env(t_state *state, char **env_name)
{
	int position = 0;
	int i = 0;
	char *str;

	(void)state;
	if (!env_name[1])
	{
		return (-1);
	}
	i = 1;
	while (i < ft_size_table(env_name))
	{
		str = ft_strjoin(env_name[i], "=");
		position = ft_find_env_position(state->g_env, str);
		if (position < 0)
		{
			ft_free(str);
			return (-1);
		}
		ft_free(str);
		ft_free(state->g_env[position]);
		while (state->g_env[position + 1])
		{
			state->g_env[position] = state->g_env[position + 1];
			position++;
		}
		state->g_env[position] = 0;
		i++;
	}
	return (1);
}

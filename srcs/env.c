/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:56:24 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/20 11:56:42 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
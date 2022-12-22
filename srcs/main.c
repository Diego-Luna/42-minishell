/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:50:01 by dluna-lo          #+#    #+#             */
/*   Updated: 2022/12/22 14:35:02 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**g_env;

int	ft_array_table(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i + 1);
}

void	*ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

void	**ft_free_table(char **array)
{
	int	i;

	if (!array)
		return (NULL);
	i = -1;
	while (array[++i])
	{
		if (array[i])
			array[i] = ft_free(array[i]);
	}
	array = ft_free(array);
	return (NULL);
}


char	**ft_crate_env(char **old, int size, int f)
{
	char	**new;
	int		i;

	if (old == NULL)
		return (NULL);
	new = ft_calloc(sizeof(char *), (ft_array_table(old) + size));
	if (!new)
		return (NULL);
	i = -1;
	while (old[++i])
		new[i] = ft_strdup(old[i]);
	if (f == 1)
		ft_free_table(old);
	return (new);
}

int	main(int argc, char **argv, char **envp)
{
	t_state	state;

	(void)argc;
	(void)argv;
	char *line;

	g_env = ft_crate_env(envp, 0, 0);
	state.i = 0;
	ft_signals();
	while (1)
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

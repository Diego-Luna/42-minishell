/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrembla <mtrembla@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:50:01 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/16 11:08:04 by mtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**g_env;

// returns the size of an array
int	ft_array_table(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i + 1);
}

// we make free, and we put at the end a null. 
void	*ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

// We free a table
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
	// t_state		state;
	t_tokens	tokens;

	(void)argc;
	(void)argv;
	(void)envp;
	// state.i = 1;
	
	char *line;

	// g_env = ft_crate_env(envp, 0, 0);
	// state.i = 0;
	ft_signals();
	while (1)
	{
    	line = readline("minishell$> ");
		if (line && *line)
			add_history(line);
		if (!line)
			break;
		ft_parse(line, &tokens);
		free(line);	
	}
	rl_clear_history();
    return (0);
}

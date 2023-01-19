/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 12:32:17 by diegofranci       #+#    #+#             */
/*   Updated: 2023/01/19 12:00:25 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// The global variable that stores environment variables
// extern char	**g_env;

char *ft_clean_str(char *str)
{
	int i = 0;
	int size = 0;
	char *new;

	if (!str[i])
	{
		return NULL;
	}
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 1)
		{
			size++;
		}
		i++;
	}
	new = calloc(sizeof(char), size + 1);
	i = 0;
	size = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 1)
		{
			new[size] = str[i];
			size++;
		}
		i++;
	}
	return (new);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegofranciscolunalopez <diegofrancisco    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 12:32:17 by diegofranci       #+#    #+#             */
/*   Updated: 2023/01/14 12:32:38 by diegofranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// The global variable that stores environment variables
extern char	**g_env;

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
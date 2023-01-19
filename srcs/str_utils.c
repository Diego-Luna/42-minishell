/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 12:32:17 by diegofranci       #+#    #+#             */
/*   Updated: 2023/01/19 16:08:09 by dluna-lo         ###   ########.fr       */
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

	if (!str)
	{
		return NULL;
	}
	while (str[i])
	{
		// if (str[i] != ' ' || str[i] != '\t')
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
		// if (str[i] != ' ' || str[i] != '\t')
		if (ft_isalnum(str[i]) == 1)
		{
			new[size] = str[i];
			size++;
		}
		i++;
	}
	return (new);
}
char *ft_clean_space_str(char *str)
{
	int i = 0;
	int ii = 0;
	int size = 0;
	int clean = 0;
	char *new;

	if (!str)
	{
		return NULL;
	}
	if (str[0] != ' ')
	{
		size = ft_strlen(str);
		clean = 1;
	}else
	{
		while (str[i] && str[i] == ' ')
		{
			i++;
		}
		ii = ft_strlen(str) - 1;
		while (str[ii] && str[ii] == ' ')
		{
			ii--;
		}
		size = ii -  i;
	}
	new = calloc(sizeof(char), size + 1);
	if (clean == 1)
	{
		i = 0;
		while (str[i])
		{
			new[i] = str[i];
			i++;
		}
	}
	else
	{
		size = 0;
		while (i <= ii)
		{
			new[size] = str[i];
			size++;
			i++;
		}
	}
	return (new);
}

int	ft_strchr_get(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			return (i);
		}
		i++;
	}
	if (s[i] == (char)c)
	{
		return (i);
	}
	return (-1);
}

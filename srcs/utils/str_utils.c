/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegofranciscolunalopez <diegofrancisco    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 12:32:17 by diegofranci       #+#    #+#             */
/*   Updated: 2023/01/21 20:01:03 by diegofranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		// if (ft_isalnum(str[i]) == 1)
		if (str[i] != ' ' || str[i] != '\t')
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
		// if (ft_isalnum(str[i]) == 1)
		if (str[i] != ' ' || str[i] != '\t')
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

void	ft_str_to_str(char *dst, char *src)
{
	int i = 0;
	int ii = 0;

	if (!src || !dst)
	{
		return;
	}
	i = ft_strlen(dst);
	while (src[ii])
	{
		dst[i] = src[ii];
		ii++;
		i++;
	}
}

int	ft_str_in_str(char *str, char *find)
{
	int i = 0;
	int i_save = 0;
	int ii = 0;
	// int size;

	if (!find)
	{
		return(-1);
	}
	while (str[i])
	{
		ii = 0;
		i_save = i;
		while (find[ii] && str[i] == find[ii])
		{
			if (!find[ii + 1] && find[ii] != str[i + 1])
			{
				return (i_save);
			}
			ii++;
			i++;
		}
		i = i_save;
		i++;
	}
	return (-1);
}
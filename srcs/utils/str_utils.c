/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 12:32:17 by diegofranci       #+#    #+#             */
/*   Updated: 2023/01/25 16:56:44 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_clean_str_value_in_new(char *str, char *new)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] != ' ' || str[i] != '\t')
		{
			new[size] = str[i];
			size++;
		}
		i++;
	}
}

char	*ft_clean_str(char *str)
{
	int		i;
	int		size;
	char	*new;

	i = 0;
	size = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] != ' ' || str[i] != '\t')
			size++;
		i++;
	}
	new = ft_calloc(sizeof(char), size + 1);
	ft_clean_str_value_in_new(str, new);
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
	int	i;
	int	ii;

	i = 0;
	ii = 0;
	if (!src || !dst)
	{
		return ;
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
	int	i;
	int	i_save;
	int	ii;

	i = 0;
	ii = 0;
	i_save = 0;
	if (!find)
		return (-1);
	while (str[i])
	{
		ii = 0;
		i_save = i;
		while (find[ii] && str[i] == find[ii])
		{
			if (!find[ii + 1] && find[ii] != str[i + 1])
				return (i_save);
			ii++;
			i++;
		}
		i = i_save;
		i++;
	}
	return (-1);
}

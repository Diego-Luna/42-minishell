/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_space_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:02:17 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/26 11:47:12 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_clean_space_str_size(char *str)
{
	int	i;
	int	ii;
	int	size;

	i = 0;
	ii = 0;
	while (str[i] && str[i] == ' ')
	{
		i++;
	}
	ii = ft_strlen(str) - 1;
	while (ii > 0 && str[ii] && str[ii] == ' ')
	{
		ii--;
	}
	size = ii - i;
	return (size);
}

int	ft_size_end_utils(char *str)
{
	int	ii;

	ii = ft_strlen(str) - 1;
	while (ii > 0 && str[ii] && str[ii] == ' ')
	{
		ii--;
	}
	return (ii);
}

int	ft_size_start_utils(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
	{
		i++;
	}
	return (i);
}

void	ft_clean_space_str_create_new(int clean, char *new, char *str)
{
	int	i;
	int	size;

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
		i = ft_size_start_utils(str);
		while (i <= ft_size_end_utils(str))
		{
			new[size] = str[i];
			size++;
			i++;
		}
	}
}

char	*ft_clean_space_str(char *str)
{
	int		ii;
	int		size;
	int		clean;
	char	*new;

	ii = 0;
	size = 0;
	clean = 0;
	if (!str)
		return (NULL);
	if (str[0] != ' ')
	{
		size = ft_strlen(str);
		clean = 1;
	}
	else
		size = ft_clean_space_str_size(str);
	if (size < 0)
		size = 0;
	new = ft_calloc(sizeof(char), size + 2);
	if (size == 0)
		return (new);
	ft_clean_space_str_create_new(clean, new, str);
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_only_str_isalnum.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:55:32 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/25 17:04:20 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_only_str_isalnum_if(char *str, int i)
{
	if (!(str[i] == ' ' || str[i] == '\'' || str[i] == '\"' || str[i] == '.'
			|| str[i] == ',' || str[i] == '(' || str[i] == ')'))
	{
		return (1);
	}
	return (0);
}

int	ft_only_str_isalnum_size(char *str)
{
	int	i;
	int	on;
	int	size;

	i = 0;
	on = 1;
	size = 0;
	while (str[i])
	{
		if (on == 1 && ft_only_str_isalnum_if(str, i) == 1)
		{
			on = 0;
			size++;
		}
		else if (on == 0 && ft_only_str_isalnum_if(str, i) == 1)
			size++;
		else if (on == 0)
			on = 2;
		i++;
	}
	return (size);
}

void	ft_only_str_isalnum_create(char *str, char *new)
{
	int	i;
	int	on;
	int	size;

	i = 0;
	size = 0;
	on = 1;
	while (str[i])
	{
		if (on == 1 && ft_only_str_isalnum_if(str, i) == 1)
		{
			on = 0;
			new[size] = str[i];
			size++;
		}
		else if (on == 0 && ft_only_str_isalnum_if(str, i) == 1)
		{
			new[size] = str[i];
			size++;
		}
		else if (on == 0)
			on = 2;
		i++;
	}
}

char	*ft_only_str_isalnum(char *str)
{
	int		size;
	char	*new;

	if (!str)
		return (NULL);
	size = ft_only_str_isalnum_size(str);
	new = ft_calloc(sizeof(char), size + 1);
	ft_only_str_isalnum_create(str, new);
	return (new);
}

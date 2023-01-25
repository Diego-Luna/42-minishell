/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:51:06 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/25 15:01:46 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_only_char(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

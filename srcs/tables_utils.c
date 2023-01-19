/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tables_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:18:43 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/19 12:22:56 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// returns the size of an array
int	ft_size_table(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		i++;
	}
	return (i);
}
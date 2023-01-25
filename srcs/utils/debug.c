/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:54:32 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/25 13:54:58 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_table_debug(char **table)
{
	int i = 0;

	printf("\n Table \n");
	while (table[i])
	{
		printf("-> {%d} srt{%s} \n", i, table[i]);
		i++;
	}
}
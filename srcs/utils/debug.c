/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:54:32 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/25 15:43:24 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_table_debug(char **table)
{
	int	i;

	i = 0;
	printf("\n Table \n");
	while (table[i])
	{
		printf("-> {%d} srt{%s} \n", i, table[i]);
		i++;
	}
}

/* Function for debug, which shows us all the created commands and their
	information. */

void	ft_print_cmds_utils(char **table, char *txt)
{
	int	ii;

	ii = 0;
	while (table && table[ii])
	{
		ft_printf("%s{%s} ", txt, table[ii]);
		ii++;
	}
}

void	ft_print_cmds(t_state *state)
{
	int	i;
	int	ii;
	int	iii;

	i = 0;
	ii = 0;
	iii = 0;
	ft_printf("\n ft_print_cmds \n");
	while (state->cmd_nmbs && i < state->cmd_nmbs)
	{
		ft_printf("id{%i} cmd{%s} ", state->cmds[i].id, state->cmds[i].cmd);
		ft_print_cmds_utils(state->cmds[i].cmd_args, "cmd_args");
		ft_print_cmds_utils(state->cmds[i].t_redirection, "cmd_args");
		ft_printf("\n");
		i++;
	}
}

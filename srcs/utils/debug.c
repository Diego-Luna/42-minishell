/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:54:32 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/25 14:04:57 by dluna-lo         ###   ########.fr       */
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

/* Function for debug, which shows us all the created commands and their
	information. */
void ft_print_cmds(t_state *state)
{
	int i = 0 ;
	int ii = 0;
	int iii = 0;

	ft_printf("\n ft_print_cmds \n");
	while (state->cmd_nmbs && i < state->cmd_nmbs)
	{
		ft_printf("id{%i} cmd{%s} ", state->cmds[i].id, state->cmds[i].cmd);
		ii = 0;
		// while (state->cmds[i].cmd_args && ii < state->cmd_nmbs && state->cmds[i].cmd_args[ii])
		while (state->cmds[i].cmd_args && state->cmds[i].cmd_args[ii])
		{
			ft_printf("cmd_args{%s} ", state->cmds[i].cmd_args[ii]);
			ii++;
		}
		iii = 0;
		while (state->cmds[i].t_redirection && state->cmds[i].t_redirection[iii])
		{
			ft_printf("t_redirection{%s} ", state->cmds[i].t_redirection[iii]);
			iii++;
		}
		ft_printf("\n");
		i++;
	}
}

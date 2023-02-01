/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:52:38 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/02/01 15:19:04 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_table(char **str, int new_line)
{
	int	i;
	int	size;

	i = 0;
	if (!str || !str[0])
		return ;
	size = ft_size_table(str);
	while (str[i])
	{
		if (new_line >= 1)
			printf("%s\n", str[i]);
		else
		{
			if (i == 0)
				printf("%s", str[i]);
			else if (i == size - 1)
				printf(" %s", str[i]);
			else
				printf(" %s", str[i]);
		}
		i++;
	}
}

void	ft_echo(t_state *state)
{
	char	**past;
	int		size;

	past = state->cmds[state->index].cmd_args;
	size = ft_size_table(past);
	if (size == 1)
	{
		printf("\n");
		return ;
	}
	else if (size >= 2 && ft_strncmp(past[1], "-n", 2) == 0
		&& ft_is_only_char(past[1] + 2, 'n') == 1)
	{
		ft_print_table(past + 2, 0);
		return ;
	}
	else if (size >= 2)
	{
		ft_print_table(past + 1, 0);
		printf("\n");
		return ;
	}
}

void	ft_comand_pwd(t_state *state)
{
	char	*str_tem;

	str_tem = NULL;
	str_tem = getcwd(NULL, 0);;
	if (!str_tem)
	{
		ft_error_message(M_ERROR_PATH, state->t_comands, state, N_ERROR_PATH);
		return ;
	}
	printf("%s\n", str_tem);
	ft_free(str_tem);
}

void	ft_comand_exit(t_state *state, char **run_comand)
{
	state->stop = STOP;
	state->exit = 0;
	if (ft_size_table(run_comand) == 2)
	{
		if ((run_comand[1][0] == '-' && ft_isdigit_str(run_comand[1] + 1) == 1) || ft_isdigit_str(run_comand[1]) == 1)
		{
			state->exit = ft_atoi(run_comand[1]);
		}
		else
		{
			ft_error_message(M_ERROR_NUMERIC_ARGUMENTS, run_comand + 1, state,
				N_ERROR_NUMERIC_ARGUMENTS);
			state->exit = 255;
		}
	}
}

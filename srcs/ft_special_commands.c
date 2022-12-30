/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_special_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:05:18 by dluna-lo          #+#    #+#             */
/*   Updated: 2022/12/29 18:40:30 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**g_env;

int ft_is_special_commands(char	*comand)
{
	if (ft_strncmp(comand, "echo", 4) == 0)
	{
		return (1);
	}
	if (ft_strncmp(comand, "cd", 2) == 0)
	{
		return (2);
	}
	if (ft_strncmp(comand, "pwd", 3) == 0)
	{
		return (3);
	}
	if (ft_strncmp(comand, "export", 6) == 0)
	{
		return (4);
	}
	if (ft_strncmp(comand, "unset", 5) == 0)
	{
		return (5);
	}
	if (ft_strncmp(comand, "env", 3) == 0)
	{
		return (6);
	}
	if (ft_strncmp(comand, "exit", 4) == 0)
	{
		return (7);
	}
	return (0);
}

void	ft_print_table(char **str)
{
	int i;

	i = 0;
	if (!str[0])
	{
		return ;
	}
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}

int ft_execve(t_state *state)
{
	int error;
	int comand;
	char *str_tem = NULL;

	error = 0;
	comand = ft_is_special_commands(state->cmds[state->index].cmd_args[0]);
	if (comand == 7){
		exit(0);
	}else if (comand == 6)
	{
		ft_print_table(g_env);
		// exit(0);
	}
	else if (comand == 3){
		str_tem = ft_find_env(g_env, state, "PWD");
		if (!str_tem)
		{
			ft_error_message(M_ERROR_PATH, state->t_comands, state, N_ERROR_PATH);
		}
		ft_printf("%s\n", str_tem);
		// exit(0);
	}else{
		error = execve(state->cmds[state->index].cmd, state->cmds[state->index].cmd_args, g_env);
		return (error);
	}
	exit(0);
	return (error);
}
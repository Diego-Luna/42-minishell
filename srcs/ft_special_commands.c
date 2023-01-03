/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_special_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:05:18 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/03 13:11:22 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**g_env;

// falta
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

// falta
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

// falta
int ft_find_env_position(char **envp, t_state *state, char *path)
{
	int	i;
	int	size;
	char **table;

	i = 0;
	size = ft_size_table(envp);
	while (i < size && ft_strncmp(path, envp[i], ft_strlen(path)))
	{
		i++;
	}
	if (i == size)
	{
		return (-1);
	}
	return (i);
}

// falta
int ft_delate_env(t_state *state)
{
	int position;
	char **copy;

	if (!state->cmds[state->index].cmd_args[1])
	{
		ft_error_message(M_ERROR_UNSET_MISSING, NULL, state, N_ERROR_UNSET_MISSING);
		return (-1);
	}
	position = ft_find_env_position(g_env, state, state->cmds[state->index].cmd_args[1]);
	if (position < 0)
	{
		ft_error_message(M_ERROR_UNSET_NOT_EXIST, &state->cmds[state->index].cmd_args[1], state, N_ERROR_UNSET_NOT_EXIST);
		return (-1);
	}
	ft_free(g_env[position]);
	while (g_env[position + 1])
	{
		g_env[position] = g_env[position + 1];
		position++;
	}
	g_env[position] = 0;
	return (1);
}

// falta
int ft_execve(t_state *state)
{
	int error;
	int comand;
	char *str_tem = NULL;

	error = 0;
	comand = ft_is_special_commands(state->cmds[state->index].cmd_args[0]);
	if (comand == 7){
		exit(0);
	}
	else if (comand == 6)
	{
		ft_print_table(g_env);
		exit(0);
	}
	else if (comand == 5)
	{
		exit(0);
	}
	else if (comand == 4)
	{
		exit(0);
	}
	else if (comand == 3)
	{
		str_tem = ft_find_env(g_env, state, "PWD");
		if (!str_tem)
		{
			ft_error_message(M_ERROR_PATH, state->t_comands, state, N_ERROR_PATH);
		}
		ft_printf("%s\n", str_tem);
		exit(0);
	}
	else
	{
		if (ft_find_env(g_env, state, "PATH") == NULL)
		{
			ft_error_message(M_ERROR_FIND_ENV, NULL, state, N_ERROR_FIND_ENV);
			exit(5);
		}
		state->cmds[state->index].cmd = ft_get_comand_p(state->cmd_paths, state->cmds[state->index].cmd_args[0]);
		if (!state->cmds[state->index].cmd)
		{
			ft_error_message(M_ERROR_PATH, state->t_comands, state, N_ERROR_PATH);
			exit(5);
		}
		error = execve(state->cmds[state->index].cmd, state->cmds[state->index].cmd_args, g_env);
		return (error);
	}
	return (error);
}

int ft_add_env(t_state *state)
{
	int size;
	int temp_leng;
	char *temp;
	char **past;
	int i;

	past = state->cmds[state->index].cmd_args;
	i = 0;
	if (ft_size_table(past) > 2)
	{
		ft_error_message(M_ERROR_UNSET_MISSING, NULL, state, N_ERROR_UNSET_MISSING);
		return (-1);
	}
	if (ft_size_table(past) == 1)
	{
		while (g_env[i])
		{
			printf("[%i]%s\n", i, g_env[i]);
			i++;
		}
		return 1;
	}
	temp_leng = ft_strlen(past[1]);
	temp = ft_calloc(sizeof(char), temp_leng);
	while (past[1][i] && past[1][i] != '=')
	{
		temp[i] = past[1][i];
		i++;
	}
	if (ft_find_env(g_env, state, temp))
	{
		size = ft_find_env_index(g_env, temp);
		g_env[size] = ft_free(g_env[size]);
	}
	else
	{
		size = ft_size_table(g_env);
		g_env = ft_crate_env(g_env, 2, 1);
	}
	g_env[size] = ft_strdup(past[1]);
	ft_free(temp);
	return (1);
}

// falta
void	ft_run_unset_export(t_state *state)
{
	int error;
	int comand;

	error = 0;
	comand = ft_is_special_commands(state->cmds[state->index].cmd_args[0]);

	if (comand == 5)
	{
		ft_delate_env(state);
	}
	if (comand == 4)
	{
		ft_add_env(state);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_comand_build.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:58:12 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/24 14:20:57 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_table(char **str, int new_line)
{
	int i;
	int size;

	i = 0;
	if (!str[0])
	{
		return ;
	}
	size = ft_size_table(str);
	while (str[i])
	{
		if (new_line >= 1)
		{
			printf("%s\n", str[i]);
		}
		else
		{
			if (i == 0)
			{
				printf("%s", str[i]);
			}else if (i == size - 1)
			{
				printf(" %s", str[i]);
			}else
			{
				printf(" %s", str[i]);
			}
		}
		i++;
	}
}

int ft_is_only_char(char *str, int c)
{
	int i = 0;

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

void	ft_echo(t_state *state)
{
	char **past;
	int size;

	past = state->cmds[state->index].cmd_args;
	size = ft_size_table(past);
	if (size == 1)
	{
		printf("\n");
		return;
	}
	else if (size >= 2 && ft_strncmp(past[1], "-n", 2) == 0 && ft_is_only_char(past[1] + 2, 'n') == 1)
	{
		ft_print_table(past + 2, 0);
		return;
	}
	// else if (size >= 2 && ft_strncmp(past[1], "-n\0", 3) != 0)
	else if (size >= 2)
	{
		ft_print_table(past + 1, 0);
		printf("\n");
		return ;
	}
}

void	ft_comand_cd(t_state *state)
{
	char **past;
	char **tem_comand;
	char **tem;
	char *path;
	char *error;

	past = state->cmds[state->index].cmd_args;
	if (ft_size_table(past) == 1)
	{
		path = ft_find_env(state->g_env, "HOME=");
		if(!path)
		{
			error = ft_strdup("HOME");
			ft_error_message(M_ERROR_PATH, &error, state, N_ERROR_PATH);
			ft_free(error);
		}
	}
	if (ft_size_table(past) >= 2)
	{
		path = state->cmds[state->index].cmd_args[1];
	}
	if (path != NULL && chdir(path) == 0)
	{
		tem = calloc(sizeof(char *), 3);
		tem_comand = calloc(sizeof(char *), 3);
		tem_comand[1] = ft_strdup("OLDPWD");
		ft_delate_env(state, tem_comand);
		tem[0] = ft_find_env(state->g_env, "PWD=");
		tem[1] = ft_strjoin("OLDPWD=", tem[0]);
		ft_add_env(state, tem);
		tem[1] = ft_free(tem[1]);
		tem_comand[1] = ft_free(tem_comand[1]);
		tem_comand[1] = ft_strdup("PWD");
		ft_delate_env(state, tem_comand);
		tem[0] = getcwd(NULL, 0);
		tem[1] = ft_strjoin("PWD=", tem[0]);
		ft_add_env(state, tem);
		ft_free(tem[0]);
		ft_free(tem[1]);
		ft_free(tem_comand[0]);
		ft_free(tem_comand[1]);
		ft_free(tem);
		ft_free(tem_comand);
	}
	else if (path != NULL)
	{
		tem = calloc(sizeof(char *), 3);
		tem[0] = ft_strdup(path);
		ft_error_message(M_ERROR_NO_EXIST, tem, state, N_ERROR_NO_EXIST);
		ft_free_table(tem);
	}
}

void	ft_comand_pwd(t_state *state)
{
	char *str_tem = NULL;

	str_tem = ft_find_env(state->g_env, "PWD=");
	if (!str_tem)
	{
		ft_error_message(M_ERROR_PATH, state->t_comands, state, N_ERROR_PATH);
		return;
	}
	printf("%s\n", str_tem);
}

void	ft_comand_exit(t_state *state, 	char **run_comand)
{
	state->stop = STOP;
	state->exit = 0;
	if (ft_size_table(run_comand) == 2)
	{
		if (ft_isdigit_str(run_comand[1]) == 1)
		{
			state->exit = ft_atoi(run_comand[1]);
		}
		else
		{
			ft_error_message(M_ERROR_NUMERIC_ARGUMENTS, run_comand + 1, state, N_ERROR_NUMERIC_ARGUMENTS);
			state->exit = 255;
		}
	}
}

int	ft_run_comand_build(t_state *state)
{
	char *comand;
	char **run_comand;

	run_comand = state->cmds[state->index].cmd_args;
	comand = run_comand[0];
	if (!comand)
		return (1);
	if (ft_strncmp(comand, "exit\0", 5) == 0)
	{
		ft_comand_exit(state, run_comand);
	}
	else if (ft_strncmp(comand, "env\0", 4) == 0)
	{
		ft_print_table(state->g_env, 1);
	}
	else if (ft_strncmp(comand, "unset\0", 6) == 0)
	{
		ft_delate_env(state, run_comand);
	}
	else if (ft_strncmp(comand, "export\0", 7) == 0)
	{
		ft_add_env(state, run_comand);
	}
	else if (ft_strncmp(comand, "echo\0", 5) == 0)
	{
		ft_echo(state);
	}
	else if (ft_strncmp(comand, "pwd\0", 4) == 0)
	{
		ft_comand_pwd(state);
	}
	else if (ft_strncmp(comand, "cd\0", 3) == 0)
	{
		ft_comand_cd(state);
	}
	else
	{
		return (0);
	}
	return (1);
}
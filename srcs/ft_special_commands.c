/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_special_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:05:18 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/18 19:28:55 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**g_env;

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

// look in a char table and return the position of it
int ft_find_env_position(char **envp, char *path)
{
	int	i;
	int	ii;
	int	size;

	i = 0;
	size = ft_size_table(envp);
	ii = ft_strlen(path);
	while (i < size && ft_strncmp(path, envp[i], ii))
	{
		i++;
	}
	if (i == size)
	{
		return (-1);
	}
	return (i);
}

int ft_delate_env(t_state *state, char **env_name)
{
	int position = 0;
	int i = 0;
	char *str;

	(void)state;
	if (!env_name[1])
	{
		return (-1);
	}
	i = 1;
	while (i < ft_size_table(env_name))
	{
		str = ft_strjoin(env_name[i], "=");
		position = ft_find_env_position(g_env, str);
		if (position < 0)
		{
			ft_free(str);
			return (-1);
		}
		ft_free(str);
		ft_free(g_env[position]);
		while (g_env[position + 1])
		{
			g_env[position] = g_env[position + 1];
			position++;
		}
		g_env[position] = 0;
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
	else if (size >= 2 && ft_strncmp(past[1], "-n", 2) > 0)
	{
		ft_print_table(past + 1, 0);
		printf("\n");
		return ;
	}
	else if (size >= 2 && ft_strncmp(past[1], "-n", 2) == 0)
	{
		ft_print_table(past + 2, 0);
		return;
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
		path = ft_find_env(g_env, "HOME=");
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
		tem[0] = ft_find_env(g_env, "PWD=");
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

	str_tem = ft_find_env(g_env, "PWD=");
	if (!str_tem)
	{
		ft_error_message(M_ERROR_PATH, state->t_comands, state, N_ERROR_PATH);
		return;
	}
	printf("%s\n", str_tem);
}

// Our own execve
int ft_execve(t_state *state)
{
	int error;
	char *erro_path;
	int i = state->index;
	// char *point;

 	if(access(state->cmds[i].cmd_args[0], X_OK | F_OK) != -1)
	{
		ft_close_fd();
		error = execve(state->cmds[i].cmd_args[0], state->cmds[i].cmd_args, g_env);
		return (error);
	}
	if (ft_find_env(g_env, "PATH=") == NULL)
	{
		erro_path = ft_strdup("PATH=");
		ft_error_message(M_ERROR_FIND_ENV, &erro_path, state, N_ERROR_FIND_ENV);
		ft_free(erro_path);
		ft_close_fd();
		exit(1);
	}
	state->env_path = ft_find_env(g_env, "PATH=");
	state->cmd_paths = ft_split(state->env_path, ':');
	state->cmds[i].cmd = ft_get_comand_p(state->cmd_paths, state->cmds[i].cmd_args[0]);
	if (!state->cmds[i].cmd)
	{
		ft_error_message(M_ERROR_PATH, state->cmds[i].cmd_args, state, N_ERROR_PATH);
		ft_close_fd();
		exit(1);
	}
	ft_close_fd();
	error = execve(state->cmds[i].cmd, state->cmds[i].cmd_args, g_env);
	return (error);
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
		state->stop = STOP;
	}
	else if (ft_strncmp(comand, "env\0", 4) == 0)
	{
		ft_print_table(g_env, 1);
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

void ft_env_export(char *str)
{
	char *temp;
	int size;
	int temp_leng;
	int i = 0;

	temp_leng = ft_strlen(str);
	temp = ft_calloc(sizeof(char), temp_leng + 1);
	while (str[i] && str[i] != '=')
	{
		temp[i] = str[i];
		i++;
	}
	if (ft_find_env(g_env, temp))
	{
		size = ft_find_env_index(g_env, temp);
		g_env[size] = ft_free(g_env[size]);
	}
	else
	{
		size = ft_size_table(g_env);
		g_env = ft_crate_env(g_env, 2, 1);
	}
	g_env[size] = ft_strdup(str);
	ft_free(temp);
}

int ft_add_env(t_state *state, char **past)
{
	int i;

	i = 0;
	(void)state;
	if (ft_size_table(past) == 1)
	{
		while (g_env[i])
		{
			printf("[%i]%s\n", i, g_env[i]);
			i++;
		}
		return 1;
	}
	if (ft_strchr(past[1], '=') == NULL)
	{
		return 0;
	}
	i = 1;
	while (i < ft_size_table(past))
	{
		ft_env_export(past[i]);
		i++;
	}

	return (1);
}

void	ft_handle_error_pipe(t_state *state)
{
	char **tem_comand;
	char *status;

	// if (state->fork_error == 256)
	if (state->fork_error > 0)
	{
		state->fork_error = 127;
	}
	status = ft_itoa(state->fork_error);
	tem_comand = calloc(sizeof(char *), 3);
	tem_comand[0] = ft_strdup("env");
	tem_comand[1] = ft_strjoin("?=", status);
	ft_add_env(state, tem_comand);
	ft_free(status);
	ft_free(tem_comand[0]);
	ft_free(tem_comand[1]);
	ft_free(tem_comand);
}
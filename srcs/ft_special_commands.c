/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_special_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:05:18 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/11 13:28:30 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**g_env;

// This function checks if the command is a special one or not, and if it is, it returns the corresponding number.
int ft_is_special_commands(char	*comand)
{
	if (ft_strncmp(comand, "echo", 4) == 0)
	{
		return (N_ECHO);
	}
	if (ft_strncmp(comand, "cd", 2) == 0)
	{
		return (N_CD);
	}
	if (ft_strncmp(comand, "pwd", 3) == 0)
	{
		return (N_PWD);
	}
	if (ft_strncmp(comand, "export", 6) == 0)
	{
		return (N_EXPORT);
	}
	if (ft_strncmp(comand, "unset", 5) == 0)
	{
		return (N_UNSET);
	}
	if (ft_strncmp(comand, "env", 3) == 0)
	{
		return (N_ENV);
	}
	if (ft_strncmp(comand, "exit", 4) == 0)
	{
		return (N_EXIT);
	}
	return (0);
}

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
	int	size;

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

// int ft_delate_env(t_state *state)
// state->cmds[state->index].cmd_args[1]
int ft_delate_env(t_state *state, char **env_name)
{
	int position;

	// if (!state->cmds[state->index].cmd_args[1])
	if (!env_name[1])
	{
		return (-1);
	}
	position = ft_find_env_position(g_env, env_name[1]);
	// position = ft_find_env_position(g_env, state->cmds[state->index].cmd_args[1]);
	if (position < 0)
	{
		ft_error_message(M_ERROR_UNSET_NOT_EXIST, &env_name[1], state, N_ERROR_UNSET_NOT_EXIST);
		// ft_error_message(M_ERROR_UNSET_NOT_EXIST, &state->cmds[state->index].cmd_args[1], state, N_ERROR_UNSET_NOT_EXIST);
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
		path = ft_find_env(g_env, state, "HOME=");
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
		tem[0] = ft_find_env(g_env, state, "PWD=");
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

	str_tem = ft_find_env(g_env, state, "PWD");
	if (!str_tem)
	{
		ft_error_message(M_ERROR_PATH, state->t_comands, state, N_ERROR_PATH);
	}
	ft_printf("%s\n", str_tem);
}

// Our own execve
int ft_execve(t_state *state)
{
	int error;
	int comand;
	char *erro_path;

	error = 0;
	comand = ft_is_special_commands(state->cmds[state->index].cmd_args[0]);
	if (comand == N_EXIT){
		exit(0);
	}
	else if (comand == N_ENV)
	{
		ft_print_table(g_env, 1);
		exit(0);
	}
	else if (comand == N_UNSET)
	{
		exit(0);
	}
	else if (comand == N_EXPORT)
	{
		exit(0);
	}
	else if (comand == N_ECHO)
	{
		ft_echo(state);
		exit(0);
	}
	else if (comand == N_PWD)
	{
		ft_comand_pwd(state);
		exit(0);
	}
	else if (comand == N_CD)
	{
		ft_comand_cd(state);
		exit(0);
	}
	else
	{
		if (ft_find_env(g_env, state, "PATH=") == NULL)
		{
			erro_path = ft_strdup("PATH=");
			ft_error_message(M_ERROR_FIND_ENV, &erro_path, state, N_ERROR_FIND_ENV);
			ft_free(erro_path);
			exit(1);
		}
		state->env_path = ft_find_env(g_env, state, "PATH=");
		state->cmd_paths = ft_split(state->env_path, ':');
		state->cmds[state->index].cmd = ft_get_comand_p(state->cmd_paths, state->cmds[state->index].cmd_args[0]);
		if (!state->cmds[state->index].cmd)
		{
			ft_error_message(M_ERROR_PATH, state->t_comands, state, N_ERROR_PATH);
			exit(1);
		}
		error = execve(state->cmds[state->index].cmd, state->cmds[state->index].cmd_args, g_env);
		return (error);
	}
	return (error);
}

int	ft_run_comand_build(t_state *state)
{
	int comand;
	char **run_comand;

	run_comand = state->cmds[state->index].cmd_args;
	comand = ft_is_special_commands(run_comand[0]);
	if (comand == N_EXIT){
		state->stop = STOP;
	}
	else if (comand == N_ENV)
	{
		ft_print_table(g_env, 1);
	}
	else if (comand == N_UNSET)
	{
		ft_delate_env(state, run_comand);
	}
	else if (comand == N_EXPORT)
	{
		ft_add_env(state, run_comand);
	}
	else if (comand == N_ECHO)
	{
		ft_echo(state);
	}
	else if (comand == N_PWD)
	{
		ft_comand_pwd(state);
	}
	else if (comand == N_CD)
	{
		ft_comand_cd(state);
	}
	else
	{
		return (0);
	}
	return (1);
}

// int ft_add_env(t_state *state)
int ft_add_env(t_state *state, char **past)
{
	int size;
	int temp_leng;
	char *temp;
	int i;

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
	temp = ft_calloc(sizeof(char), temp_leng + 1);
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

// check when it is a command that affects environment variables, so that it is executed only in the parent process
void	ft_run_unset_export(t_state *state)
{
	int error;
	int comand;
	char **run_comand;

	error = 0;
	run_comand = state->cmds[state->index].cmd_args;
	comand = ft_is_special_commands(run_comand[0]);

	if (comand == N_UNSET)
	{
		ft_delate_env(state, run_comand);
	}
	if (comand == N_EXPORT)
	{
		ft_add_env(state, run_comand);
	}
}


void	ft_handle_error_pipe(t_state *state)
{
	char **tem_comand;
	char *status;

	if (state->fork_error == 256)
	{
		state->fork_error = 127;
	}
	status = ft_itoa(state->fork_error);
	tem_comand = calloc(sizeof(char *), 3);
	tem_comand[1] = ft_strjoin("?=", status);
	ft_add_env(state, tem_comand);
	ft_free(status);
	ft_free(tem_comand[1]);
	ft_free(tem_comand);
}
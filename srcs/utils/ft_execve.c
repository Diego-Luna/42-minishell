/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:58:18 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/23 15:57:39 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../includes/minishell.h"

// Our own execve
int ft_execve(t_state *state)
{
	int error;
	char **erro_path;
	int i = state->index;
	// char *point;

 	if(access(state->cmds[i].cmd_args[0], X_OK | F_OK) != -1)
	{
		ft_close_fd();
		error = execve(state->cmds[i].cmd_args[0], state->cmds[i].cmd_args, state->g_env);
		return (error);
	}
	if (ft_find_env(state->g_env, "PATH=") == NULL)
	{
		erro_path = ft_calloc(sizeof(char *) , 2);
		erro_path[0] = ft_strdup("PATH");
		ft_error_message(M_ERROR_FIND_ENV, erro_path, state, N_ERROR_FIND_ENV);
		ft_free_table(erro_path);
		ft_close_fd();
		// exit(1);
		exit(errno);
	}
	state->env_path = ft_find_env(state->g_env, "PATH=");
	state->cmd_paths = ft_split(state->env_path, ':');
	state->cmds[i].cmd = ft_get_comand_p(state->cmd_paths, state->cmds[i].cmd_args[0]);
	if (!state->cmds[i].cmd)
	{
		ft_error_message(M_ERROR_PATH, state->cmds[i].cmd_args, state, N_ERROR_PATH);
		ft_close_fd();
		// exit(1);
		exit(errno);
	}
	ft_close_fd();
	error = execve(state->cmds[i].cmd, state->cmds[i].cmd_args, state->g_env);
	return (error);
}

void ft_env_export(t_state *state ,char *str)
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
	if (ft_find_env(state->g_env, temp))
	{
		size = ft_find_env_index(state->g_env, temp);
		state->g_env[size] = ft_free(state->g_env[size]);
	}
	else
	{
		size = ft_size_table(state->g_env);
		state->g_env = ft_crate_env(state->g_env, 2, 1);
	}
	state->g_env[size] = ft_strdup(str);
	ft_free(temp);
}

char **ft_only_names(char **env)
{
	int i = 0;
	int ii = 0;
	int iii = 0;
	char **new;
	char *tem;

	new = ft_calloc(sizeof(char *), ft_size_table(env) + 1);

	while (env[i])
	{
		ii = ft_strchr_get(env[i], '=');
		tem = ft_calloc(sizeof(char), ii + 1);
		iii = 0;
		while (iii < ii)
		{
			tem[iii] = env[i][iii];
			iii++;
		}
		new[i] = tem;
		i++;
	}
	return (new);
}

void	ft_env_organized(char **env_original)
{
	int i = 0;
	char **env;
	char *tem;

	env = ft_only_names(env_original);
	while (env[i])
	{
		if (i >= 1 && ft_strncmp(env[i], env[i - 1], ft_strlen(env[i])) < 0)
		{
			tem = env[i - 1];
			env[i - 1] = env[i];
			env[i] = tem;
			i = 0;
		}
		i++;
	}

	i = 0;
	while (env[i])
	{
		tem = ft_strjoin(env[i], "=");
		printf("declare -x %s=\"%s\"\n", env[i], ft_find_env(env_original, tem));
		ft_free(tem);
		i++;
	}
	ft_free_table(env);
}

int ft_add_env(t_state *state, char **past)
{
	int i;

	if (ft_size_table(past) == 1)
	{
		ft_env_organized(state->g_env);
		return 1;
	}
	if (ft_strchr(past[1], '=') == NULL)
	{
		return 0;
	}
	i = 1;
	while (i < ft_size_table(past))
	{
		ft_env_export(state, past[i]);
		i++;
	}

	return (1);
}
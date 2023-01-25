/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_comand_build.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:58:12 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/25 18:04:33 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_comand_cd_utils(t_state *state)
{
	char	**tem;
	char	**tem_comand;

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

static void	ft_error_message_create_table(t_state *state, char *str, char *ms,
		int nu)
{
	char	**tem;

	tem = calloc(sizeof(char *), 3);
	tem[0] = ft_strdup(str);
	ft_error_message(ms, tem, state, nu);
	ft_free_table(tem);
}

void	ft_comand_cd(t_state *state)
{
	char	**past;
	char	*path;

	past = state->cmds[state->index].cmd_args;
	if (ft_size_table(past) == 1)
	{
		path = ft_find_env(state->g_env, "HOME=");
		if (!path)
		{
			ft_error_message_create_table(state, "HOME", M_ERROR_NO_EXIST,
				N_ERROR_NO_EXIST);
		}
	}
	if (ft_size_table(past) >= 2)
		path = state->cmds[state->index].cmd_args[1];
	if (path != NULL && chdir(path) == 0)
		ft_comand_cd_utils(state);
	else if (path != NULL)
	{
		ft_error_message_create_table(state, path, M_ERROR_NO_EXIST,
			N_ERROR_NO_EXIST);
	}
}

int	ft_run_comand_build(t_state *state)
{
	char	**run_comand;
	char	*comand;

	run_comand = state->cmds[state->index].cmd_args;
	comand = run_comand[0];
	if (!comand)
		return (1);
	if (ft_strncmp(comand, "exit\0", 5) == 0)
		ft_comand_exit(state, run_comand);
	else if (ft_strncmp(comand, "env\0", 4) == 0)
		ft_print_table(state->g_env, 1);
	else if (ft_strncmp(comand, "unset\0", 6) == 0)
		ft_delate_env(state, run_comand);
	else if (ft_strncmp(comand, "export\0", 7) == 0)
		ft_add_env(state, run_comand);
	else if (ft_strncmp(comand, "echo\0", 5) == 0)
		ft_echo(state);
	else if (ft_strncmp(comand, "pwd\0", 4) == 0)
		ft_comand_pwd(state);
	else if (ft_strncmp(comand, "cd\0", 3) == 0)
		ft_comand_cd(state);
	else
		return (0);
	return (1);
}

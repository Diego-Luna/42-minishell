/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_ft_add_info_comands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:41:56 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/20 11:46:29 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_handle_env_varibles(t_state *state, int i, int ii)
{
	t_cmd *cmd;

	cmd = &state->cmds[i];
	char *path_clean;
	char *path;

	if (ft_strchr_get(cmd->cmd_args[ii], '$') >= 0 && ft_strlen(cmd->cmd_args[ii]) > (size_t)ft_strchr_get(cmd->cmd_args[ii], '$')  && ft_strlen(cmd->cmd_args[ii]) > 1)
	{
		path_clean = ft_clean_str(ft_strchr(cmd->cmd_args[ii], '$') + 1);
		path = ft_strjoin(path_clean, "=");
		if (ft_find_env(state->g_env, path) != NULL)
		{
			cmd->cmd_args[ii] = ft_free(cmd->cmd_args[ii]);
			cmd->cmd_args[ii] = ft_calloc(sizeof(char), ft_strlen(ft_find_env(state->g_env, path)) + 1);
			ft_strlcat(cmd->cmd_args[ii], ft_find_env(state->g_env, path), ft_strlen(ft_find_env(state->g_env, path)) + 1);
		}
		else if (ii > 0)
		{
			cmd->cmd_args[ii] = ft_free(cmd->cmd_args[ii]);
		}
		ft_free(path);
		ft_free(path_clean);
	}
}

void ft_add_info_comands(t_state *state)
{
	int i = 0;
	int ii = 0;
	int modife = 1;
	t_cmd *cmd;
	char *path;

	while (i < state->cmd_nmbs)
	{
		cmd = &state->cmds[i];
		ii = 0;
		while (cmd->cmd_args[ii])
		{
			if (cmd->cmd_args[ii][0] == '\'')
			{
				modife = 0;
			}
			cmd->cmd_args[ii] = ft_clean_quotes(cmd->cmd_args[ii]);
			path = ft_clean_space_str(cmd->cmd_args[ii]);
			cmd->cmd_args[ii] = ft_free(cmd->cmd_args[ii]);
			cmd->cmd_args[ii] = path;
			if (modife == 1)
			{
				ft_handle_env_varibles(state, i, ii);
			}
			ii++;
		}
		ii = 0;
		while (cmd->t_redirection && cmd->t_redirection[ii])
		{
			cmd->t_redirection[ii] = ft_clean_quotes(cmd->t_redirection[ii]);
			ii++;
		}
		if (cmd->redirect == 1)
		{
			state->index = i;
			ft_redirection_two(state, 0);
		}
		if (cmd->redirect == 3)
		{
			state->index = i;
			ft_redirection_four(state, 0);
		}
		if (cmd->redirect == 2)
		{
			ft_create_herodoc(state, i);
		}
		i++;
	}
}

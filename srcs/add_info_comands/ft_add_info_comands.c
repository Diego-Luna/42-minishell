/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_info_comands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:41:56 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/23 15:51:19 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *ft_modif(char *cmd_args, char **env, int ii)
{
	char *path_clean;
	char *path;
	char *new;
	int plus = 0;
	int i = 0;

	(void)ii;
	new = NULL;
	path_clean = ft_only_str_isalnum(cmd_args);
	path = ft_strjoin(path_clean, "=");
	plus = ft_strlen(cmd_args) - ft_strlen(path_clean);
	if (ft_find_env(env, path) != NULL)
	{
		new = ft_calloc(sizeof(char), ft_strlen(ft_find_env(env, path)) + plus + 1);
		ft_strlcat(new, ft_find_env(env, path), ft_strlen(ft_find_env(env, path)) + 1);
		ii = -1;
	}
	else if (ii > 0)
	{
		new = NULL;
		ii = -1;
		new = ft_calloc(sizeof(char), plus + 1);
	}
	else
	{
		new = cmd_args;
		ft_free(path);
		ft_free(path_clean);
		return (new);
	}

	i = ft_strlen(path_clean);
	plus = ft_strlen(new);
	while (cmd_args[i])
	{
		new[plus] = cmd_args[i];
		plus++;
		i++;
	}

	ft_free(cmd_args);
	ft_free(path);
	ft_free(path_clean);
	return (new);
}

void ft_handle_env_varibles(t_state *state, int i, int ii)
{
	t_cmd *cmd;
	char **table;
	char *new;
	int size;
	int position;

	table = NULL;
	cmd = &state->cmds[i];
	size = 0;
	position = 0;
	if (ft_strchr_get(cmd->cmd_args[ii], '$') >= 0 && ft_strlen(cmd->cmd_args[ii]) > (size_t)ft_strchr_get(cmd->cmd_args[ii], '$')  && ft_strlen(cmd->cmd_args[ii]) > 1)
	{
		table = ft_split(cmd->cmd_args[ii], '$');
		while (table[position])
		{
			table[position] = ft_modif(table[position], state->g_env, ii);
			size += ft_strlen(table[position]);
			position++;
		}
		new = ft_calloc(sizeof(char), size + 1);
		i = 0;
		while (i < position)
		{
			ft_str_to_str(new, table[i]);
			ft_free(table[i]);
			i++;
		}
		ft_free(table);
		ft_free(cmd->cmd_args[ii]);
		cmd->cmd_args[ii] = new;
	}
}

void ft_add_info_comands(t_state *state)
{
	int i = 0;
	int ii = 0;
	int modife = 1;
	t_cmd *cmd;
	char *path;

	while (i < state->cmd_nmbs && state->error == NO_ERROR)
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
			ft_free(cmd->cmd_args[ii]);
			cmd->cmd_args[ii] = NULL;
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
		if (ft_size_table(cmd->cmd_args) > 0 && cmd->redirect == 2)
		{
			ft_create_herodoc(state, i);
		}
		if ((ft_size_table(cmd->cmd_args) == 0 && cmd->redirect > -1) ||
				ft_strncmp(cmd->cmd_args[ii], "||\0", 3) == 0)
		{
			ft_error_message(M_ERROR_TOKENS_REDE, cmd->cmd_args, state, N_ERROR_TOKENS_REDE);
		}
		i++;
	}
}

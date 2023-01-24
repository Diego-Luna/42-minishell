/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_info_comands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:41:56 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/24 13:07:56 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_utils_new(char **env, char *path, int plus)
{
	char	*new;

	new = ft_calloc(sizeof(char), ft_strlen(ft_find_env(env, path)) + plus + 1);
	ft_strlcat(new, ft_find_env(env, path), ft_strlen(ft_find_env(env, path))
		+ 1);
	return (new);
}

static char	*ft_utils_free(char *str_1, char *str_2, char *str_3, char *str_4)
{
	if (str_1)
	{
		ft_free(str_1);
	}
	if (str_2)
	{
		ft_free(str_2);
	}
	if (str_3)
	{
		ft_free(str_3);
	}
	return (str_4);
}

char	*ft_modif(char *cmd_args, char **env, int ii)
{
	char	*path_clean;
	char	*path;
	char	*new;
	int		plus;
	int		i;

	plus = 0;
	i = 0;
	path_clean = ft_only_str_isalnum(cmd_args);
	path = ft_strjoin(path_clean, "=");
	plus = ft_strlen(cmd_args) - ft_strlen(path_clean);
	if (ft_find_env(env, path) != NULL && ii == 1)
		new = ft_utils_new(env, path, plus);
	else if (ii == 1)
		new = ft_calloc(sizeof(char), plus + 1);
	else
		return (ft_utils_free(path, path_clean, NULL, cmd_args));
	i = ft_strlen(path_clean);
	plus = ft_strlen(new);
	while (cmd_args[i])
	{
		new[plus++] = cmd_args[i++];
	}
	return (ft_utils_free(path, path_clean, cmd_args, new));
}

int	ft_is_delete(t_state *state, int *num, char *tem)
{
	t_cmd	*cmd;
	char	*str;

	cmd = &state->cmds[num[0]];
	str = cmd->cmd_args[num[1]];
	if (ft_str_in_str(str + num[2], tem) >= 0)
	{
		if (ft_str_in_str(str + num[2], tem) + num[2] - 1 >= 0
			&& str[ft_str_in_str(str + num[2], tem) + num[2] - 1] == '$')
		{
			num[2] = ft_str_in_str(str + num[2], tem) + 1;
			return (1);
		}
	}
	return (0);
}

int	ft_handle_env_varibles_if(t_state *state, int i, int ii)
{
	t_cmd	*cmd;

	cmd = &state->cmds[i];
	if (ft_strchr_get(cmd->cmd_args[ii], '$') >= 0
		&& ft_strlen(cmd->cmd_args[ii]) > (size_t)ft_strchr_get(cmd->cmd_args[ii],
			'$') && ft_strlen(cmd->cmd_args[ii]) > 1)
	{
		return (1);
	}

	return (0);
}

void	ft_handle_env_varibles(t_state *state, int i, int ii)
{
	t_cmd	*cmd;
	char	**table;
	char	*new;
	int		position;
	int		num[4];

	cmd = &state->cmds[i];
	num[3] = 0;
	position = 0;
	if (ft_handle_env_varibles_if(state, i, ii) == 1)
	{
		table = ft_split(cmd->cmd_args[ii], '$');
		num[0] = i;
		num[1] = ii;
		num[2] = 0;
		while (table[position])
		{
			table[position] = ft_modif(table[position], state->g_env, ft_is_delete(state, num, table[position]));
			num[3] += ft_strlen(table[position]);
			position++;
		}
		new = ft_calloc(sizeof(char), num[3] + 1);
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

void	ft_add_info_comands(t_state *state)
{
	int		i;
	int		ii;
	int		modife;
	t_cmd	*cmd;
	char	*path;

	i = 0;
	ii = 0;
	modife = 1;
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
		if (ft_size_table(cmd->t_redirection) > 0 && cmd->redirect == 2)
		{
			ft_create_herodoc(state, i);
		}
		if (cmd->cmd_args[0] && ft_strncmp(cmd->cmd_args[0], "||\0", 3) == 0)
		{
			ft_error_message(M_ERROR_TOKENS_REDE, cmd->cmd_args, state,
					N_ERROR_TOKENS_REDE);
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_info_comands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:41:56 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/30 17:39:25 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_handle_env_varibles_utils(t_state *state, int *num, int ii, int i)
{
	char	**table;
	char	*new;
	t_cmd	*cmd;

	cmd = &state->cmds[i];
	table = ft_split(cmd->cmd_args[ii], '$');
	while (table[num[4]])
	{
		table[num[4]] = ft_modif(table[num[4]], state->g_env,
				ft_is_delete(state, num, table[num[4]]));
		num[3] += ft_strlen(table[num[4]]);
		num[4]++;
	}
	new = ft_calloc(sizeof(char), num[3] + 1);
	i = 0;
	while (i < num[4])
	{
		ft_str_to_str(new, table[i]);
		ft_free(table[i]);
		i++;
	}
	ft_free(table);
	return (new);
}

void	ft_handle_env_varibles(t_state *state, int i, int ii)
{
	t_cmd	*cmd;
	char	*new;
	int		num[5];

	cmd = &state->cmds[i];
	num[3] = 0;
	num[4] = 0;
	if (ft_handle_env_varibles_if(state, i, ii) == 1)
	{
		num[0] = i;
		num[1] = ii;
		num[2] = 0;
		new = ft_handle_env_varibles_utils(state, num, ii, i);
		ft_free(cmd->cmd_args[ii]);
		cmd->cmd_args[ii] = new;
	}
}

void	ft_add_info_comands_clean(t_state *state, int i, char **table)
{
	int		modife;
	int		ii;
	char	*path;

	modife = 1;
	ii = 0;
	while (table[ii])
	{
		if (table[ii][0] == '\'')
		{
			modife = 0;
		}
		table[ii] = ft_clean_quotes(table[ii]);
		path = ft_clean_space_str(table[ii]);
		ft_free(table[ii]);
		table[ii] = NULL;
		table[ii] = path;
		if (modife == 1)
		{
			ft_handle_env_varibles(state, i, ii);
		}
		ii++;
	}
}

void ft_add_info_comands_redirection_while(t_state *state, t_cmd *cmd, int i)
{
	if ((cmd->cmd_args[0] && ft_strncmp(cmd->cmd_args[0], "||\0", 3) == 0 )|| (ft_size_table(cmd->cmd_args) == 0 && state->cmd_nmbs == 1))
	{
		ft_error_message(M_ERROR_TOKENS_REDE, cmd->cmd_args, state,
			N_ERROR_TOKENS_REDE);
		return;
	}
	if (cmd->redirect[cmd->i_redi] == 1)
	{
		state->index = i;
		ft_redirection_two(state, 0);
	}
	if (cmd->redirect[cmd->i_redi] == 3)
	{
		state->index = i;
		ft_redirection_four(state, 0);
	}
	if (ft_size_table(cmd->t_redirection) > 0 && cmd->redirect[cmd->i_redi] == 2)
	{
		ft_create_herodoc(state, i);
	}
}

void	ft_add_info_comands_redirection(t_state *state, t_cmd *cmd, int i)
{
	cmd->i_redi = 0;
	while (cmd->i_redi < cmd->n_of_redi && state->error == NO_ERROR)
	{
		ft_add_info_comands_redirection_while(state, cmd, i);
		cmd->i_redi++;
	}
	cmd->i_redi = 0;
}

void	ft_add_info_comands(t_state *state)
{
	int		i;
	int		ii;
	t_cmd	*cmd;

	i = 0;
	ii = 0;
	while (i < state->cmd_nmbs && state->error == NO_ERROR)
	{
		cmd = &state->cmds[i];
		ft_add_info_comands_clean(state, i, cmd->cmd_args);
		ii = 0;
		while (cmd->t_redirection && cmd->t_redirection[ii])
		{
			cmd->t_redirection[ii] = ft_clean_quotes(cmd->t_redirection[ii]);
			ii++;
		}
		ft_add_info_comands_redirection(state, cmd, i);
		i++;
	}
}

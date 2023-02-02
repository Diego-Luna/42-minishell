/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 10:47:26 by diegofranci       #+#    #+#             */
/*   Updated: 2023/02/02 12:15:47 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_delete_process(t_cmd *cmd)
{
	char	*number;
	char	*i_redi;
	char	*file;
	char	*file_tem;

	number = ft_itoa(cmd->id);
	i_redi = ft_itoa(cmd->i_redi);
	file_tem = ft_strjoin(number, i_redi);
	file = ft_strjoin(".heredoc_tmp_", file_tem);
	unlink(file);
	ft_free(number);
	ft_free(i_redi);
	ft_free(file_tem);
	ft_free(file);
}

void	ft_delete_herodoc(t_cmd *cmd)
{
	cmd->i_redi = 0;
	while (cmd->i_redi < cmd->n_of_redi - 1)
	{
		ft_delete_process(cmd);
		cmd->i_redi++;
	}
}

void	ft_free_comand_table(char **table)
{
	int	ii;

	ii = 0;
	while (table && table[ii])
	{
		ft_free(table[ii]);
		ii++;
	}
	ft_free(table);
}

// We make all our commandos free
void	ft_free_comand(t_state *state)
{
	int	i;
	int	ii;

	i = 0;
	ii = 0;
	state->t_comands = (char **)ft_free_table(state->t_comands);
	i = 0;
	if (!state->cmds)
	{
		return ;
	}
	while (i < state->cmd_nmbs)
	{
		ft_free_comand_table(state->cmds[i].cmd_args);
		ft_delete_herodoc(&state->cmds[i]);
		ft_free(state->cmds[i].cmd);
		ft_free(state->cmds[i].redirect);
		ft_free_comand_table(state->cmds[i].t_redirection);
		if (state->cmds[i].file > 0)
		{
			close(state->cmds[i].file);
		}
		i++;
	}
	state->cmds = ft_free(state->cmds);
}

// free to everything
void	ft_free_all(t_state *state)
{
	state->cmd_paths = (char **)ft_free_table(state->cmd_paths);
	ft_free_comand(state);
	state->t_redirection = (char **)ft_free_table(state->t_redirection);
	state->fork_error = 0;
}

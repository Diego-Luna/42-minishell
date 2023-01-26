/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 10:47:26 by diegofranci       #+#    #+#             */
/*   Updated: 2023/01/26 13:39:33 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_delete_herodoc(t_cmd *cmd)
{
	char	*number;
	char	*file;

	number = ft_itoa(cmd->id);
	file = ft_strjoin(".heredoc_tmp_", number);
	unlink(file);
	ft_free(number);
	ft_free(file);
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

void	ft_check_exit(t_state *state)
{
	ft_close_fd();
	ft_free_all(state);
}

// free to everything
void	ft_free_all(t_state *state)
{
	state->cmd_paths = (char **)ft_free_table(state->cmd_paths);
	ft_free_comand(state);
	ft_free_table(state->t_redirection);
	state->fork_error = 0;
}

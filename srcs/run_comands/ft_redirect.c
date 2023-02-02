/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 18:06:30 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/02/01 16:03:02 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// <
void	ft_redirection_one(t_state *state)
{
	int		index;
	t_cmd	*cmd;
	int		pos;

	index = state->index;
	cmd = &state->cmds[index];
	pos = cmd->i_redi;
	if (cmd->t_redirection[pos] && access(cmd->t_redirection[pos], F_OK) == -1)
	{
		ft_error_message(M_ERROR_NO_FILE_DIC, cmd->t_redirection, state,
			N_ERROR_NO_FILE_DIC);
		return ;
	}
	cmd->file = open(cmd->t_redirection[pos], O_RDONLY, 0644);
	if (!cmd->file)
	{
		return ;
	}
	dup2(cmd->file, STDIN_FILENO);
}

// >
void	ft_redirection_two(t_state *state, int is_dup2)
{
	int		index;
	t_cmd	*cmd;

	index = state->index;
	cmd = &state->cmds[index];
	cmd->file = open(cmd->t_redirection[cmd->i_redi],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (is_dup2 == 1)
	{
		dup2(cmd->file, STDOUT_FILENO);
	}
	else
	{
		close(cmd->file);
	}
}

// <<
void	ft_redirection_three(t_state *state)
{
	int		index;
	t_cmd	*cmd;
	char	*file;
	char	*file_tem;
	char	*number;
	char	*i_redi;

	index = state->index;
	cmd = &state->cmds[index];
	number = ft_itoa(cmd->id);
	i_redi = ft_itoa(cmd->i_redi);
	file_tem = ft_strjoin(number, i_redi);
	file = ft_strjoin(".heredoc_tmp_", file_tem);
	ft_free(number);
	ft_free(i_redi);
	ft_free(file_tem);
	cmd->file = open(file, O_RDONLY, 0644);
	if (cmd->file < 0)
	{

	}
	ft_free(file);
	dup2(cmd->file, STDIN_FILENO);
}

// >>
void	ft_redirection_four(t_state *state, int is_dup2)
{
	int		index;
	t_cmd	*cmd;

	index = state->index;
	cmd = &state->cmds[index];
	cmd->file = open(cmd->t_redirection[cmd->i_redi],
			O_CREAT | O_APPEND | O_RDWR, 0644);
	if (cmd->file < 0)
	{
		ft_error_message(M_ERROR_NO_FILE_DIC, cmd->t_redirection, state,
			N_ERROR_NO_FILE_DIC);
		return ;
	}
	if (is_dup2 == 1)
	{
		dup2(cmd->file, STDOUT_FILENO);
	}
	else
	{
		close(cmd->file);
	}
}

int	ft_on_redirection(t_state *state)
{
	int		type;
	int		index;
	int		positon;
	t_cmd	*cmd;

	index = state->index;
	cmd = &state->cmds[index];
	positon = 0;
	cmd->i_redi = 0;
	while (cmd->i_redi < cmd->n_of_redi)
	{
		type = cmd->redirect[cmd->i_redi];
		if (type <= -1 || cmd->i_redi == cmd->n_of_redi - 1)
			return (0);
		else if (type == 0)
			ft_redirection_one(state);
		else if (type == 1)
			ft_redirection_two(state, 1);
		else if (type == 2)
			ft_redirection_three(state);
		else if (type == 3)
			ft_redirection_four(state, 1);
		cmd->i_redi++;
	}
	return (1);
}

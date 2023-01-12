/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 18:06:30 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/12 18:47:32 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// The global variable that stores environment variables
extern char	**g_env;

void	ft_redirection_one(t_state *state)
{
	int index;
	t_cmd *cmd;

	index = state->index;
	cmd = &state->cmds[index];
	if (access(cmd->t_redirection[1], F_OK) == -1)
	{
		ft_error_message(M_ERROR_NO_FILE_DIC, cmd->t_redirection + 1, state, N_ERROR_NO_FILE_DIC);
	}
	cmd->file = open(cmd->t_redirection[1], O_RDONLY, 0644);
	dup2(cmd->file, STDIN_FILENO);
}

void	ft_redirection_two(t_state *state)
{
	int index;
	t_cmd *cmd;

	index = state->index;
	cmd = &state->cmds[index];

	cmd->file = open(cmd->t_redirection[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(cmd->file, STDOUT_FILENO);
}

void	ft_redirection_three(t_state *state)
{
	int index;
	t_cmd *cmd;
	char *str;

	index = state->index;
	cmd = &state->cmds[index];

	cmd->file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (cmd->file < 0)
	{
		ft_error_message(M_ERROR_NO_FILE_DIC, cmd->t_redirection + 1, state, N_ERROR_NO_FILE_DIC);
	}
	while (1)
	{
		write(1, "heredoc> ", 9);
		str = get_next_line(0);
		if (!ft_strncmp(cmd->t_redirection[1], str, ft_strlen(cmd->t_redirection[1]) + 1))
			break ;
		write(cmd->file, str, ft_strlen(str));
		write(cmd->file, "\n", 1);
		free(str);
	}
	free(str);
	close(cmd->file);
}





int	ft_on_redirection(t_state *state)
{
	int type;
	int index;
	t_cmd *cmd;

	index = state->index;
	cmd = &state->cmds[index];
	type = cmd->redirect;

	if (state->cmds[index].redirect == -1)
	{
		return (0);
	}
	else if (type == 0)
	{
		ft_redirection_one(state);
	}
	else if (type == 1)
	{
		ft_redirection_two(state);
	}
	else if (type == 3)
	{
		ft_redirection_three(state);
	}
	// else if (type == 4)
	// {
		
	// }
	return (1);
}

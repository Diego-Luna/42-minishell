/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 18:06:30 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/17 15:56:21 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// The global variable that stores environment variables
extern char	**g_env;

// <
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

// >
void	ft_redirection_two(t_state *state)
{
	int index;
	t_cmd *cmd;

	index = state->index;
	cmd = &state->cmds[index];

	cmd->file = open(cmd->t_redirection[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// cmd->file = open(cmd->t_redirection[1], O_WRONLY | O_CREAT | O_TRUNC);
	dup2(cmd->file, STDOUT_FILENO);
}

void	ft_create_herodoc_(t_state *state, int index)
{
	// int index;
	t_cmd *cmd;
	char *str;
	char *str_clean;
	char *file;
	char *number;

	// index = state->index;
	cmd = &state->cmds[index];
	number = ft_itoa(cmd->id);
	file = ft_strjoin(".heredoc_tmp_", number);
	ft_free(number);
	cmd->file = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (cmd->file < 0)
	{
		ft_error_message(M_ERROR_NO_FILE_DIC, cmd->t_redirection + 1, state, N_ERROR_NO_FILE_DIC);
		ft_free(file);
		return;
	}
	str_clean = ft_clean_str(cmd->t_redirection[1]);
	str = readline("heredoc_tmp > ");
	while (str)
	{
		if (ft_strncmp(str, str_clean, ft_strlen(str_clean)) == 0)
			break ;
		ft_putstr_fd(str, cmd->file);
		ft_putstr_fd("\n", cmd->file);
		ft_free(str);
		str = readline("heredoc_tmp > ");
	}
	close(cmd->file);
	ft_free(str);
	ft_free(str_clean);
	ft_free(file);
}

// <<
void	ft_redirection_three(t_state *state)
{
	int index;
	t_cmd *cmd;
	char *file;
	char *number;

	index = state->index;
	cmd = &state->cmds[index];
	number = ft_itoa(cmd->id);
	file = ft_strjoin(".heredoc_tmp_", number);
	ft_free(number);
	cmd->file = open(file, O_RDONLY, 0644);
	ft_free(file);
	dup2(cmd->file, STDIN_FILENO);
}

// >>
void	ft_redirection_four(t_state *state)
{
	int index;
	t_cmd *cmd;

	index = state->index;
	cmd = &state->cmds[index];
	cmd->file = open(cmd->t_redirection[1], O_CREAT | O_APPEND | O_RDWR, 0644);
	if (cmd->file < 0)
	{
		ft_error_message(M_ERROR_NO_FILE_DIC, cmd->t_redirection + 1, state, N_ERROR_NO_FILE_DIC);
		return;
	}
	dup2(cmd->file, STDOUT_FILENO);
	dprintf(2, "\n run >>\n");
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
	else if (type == 2)
	{
		ft_redirection_three(state);
	}
	else if (type == 3)
	{
		ft_redirection_four(state);
	}
	return (1);
}

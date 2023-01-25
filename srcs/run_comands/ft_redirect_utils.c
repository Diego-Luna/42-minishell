/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:32:17 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/25 15:32:57 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_create_herodoc_utils(t_cmd *cmd)
{
	char	*str;

	str = readline("heredoc_tmp > ");
	while (str)
	{
		if (ft_strncmp(str, cmd->t_redirection[0], ft_strlen(str)) == 0)
			break ;
		ft_putstr_fd(str, cmd->file);
		ft_putstr_fd("\n", cmd->file);
		ft_free(str);
		str = readline("heredoc_tmp > ");
	}
	ft_free(str);
}

void	ft_create_herodoc(t_state *state, int index)
{
	t_cmd	*cmd;
	char	*file;
	char	*number;

	cmd = &state->cmds[index];
	number = ft_itoa(cmd->id);
	file = ft_strjoin(".heredoc_tmp_", number);
	ft_free(number);
	cmd->file = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (cmd->file < 0)
	{
		ft_error_message(M_ERROR_NO_FILE_DIC, cmd->t_redirection, state,
			N_ERROR_NO_FILE_DIC);
		ft_free(file);
		return ;
	}
	ft_create_herodoc_utils(cmd);
	close(cmd->file);
	ft_free(file);
}

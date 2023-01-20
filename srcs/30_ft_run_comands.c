/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_ft_run_comands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:45:15 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/20 11:59:26 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// ft_get_comand_p, is in charge of finding the path of the command, for the execution of the mimes, or returns null.
char	*ft_get_comand_p(char **paths, char *cmd)
{
	char	*tem;
	char	*new_c;

	while (*paths)
	{
		tem = ft_strjoin(*paths, "/");
		new_c = ft_strjoin(tem, cmd);
		free(tem);
		if (access(new_c, 0) == 0)
			return (new_c);
		free(new_c);
		paths++;
	}
	return (NULL);
}

// The command handler
void ft_run_comands(t_state	*state)
{
	state->save_stdout = dup(STDOUT_FILENO);
	state->save_stdin = dup(STDIN_FILENO);
	state->index = 0;
	if (state->cmd_nmbs ==  1)
	{
		ft_process_comand(state);
	}
	else
	{
		ft_process_comands(state);
	}
	dup2(state->save_stdout, STDOUT_FILENO);
	dup2(state->save_stdin, STDIN_FILENO);
	close(state->save_stdin);
	close(state->save_stdout);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 10:47:26 by diegofranci       #+#    #+#             */
/*   Updated: 2023/01/20 15:02:40 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// we make free, and we put at the end a null.
void	*ft_free(void *ptr)
{
	// check if have a value, and free value
	if (ptr)
	{
		free(ptr);
	}
	return (NULL);
}

void	ft_close_fd(void)
{
	int	i;

	i = 3;
	// while (i < 101)
	while (i < 200)
	{
		close(i);
		i++;
	}
}

// We free a table
void	**ft_free_table(char **array)
{
	int	i;

	if (!array)
	{
		return (NULL);
	}
	i = -1;
	while (array[++i])
	{
		if (array[i])
		{
			// We make the value free and we put null, for convenience
			array[i] = ft_free(array[i]);
		}
	}
	// We make the value free and we put null, for convenience
	array = ft_free(array);
	return (NULL);
}

void	ft_delete_herodoc(t_cmd *cmd)
{
	char *number;
	char *file;

	number = ft_itoa(cmd->id);
	file = ft_strjoin(".heredoc_tmp_", number);
	unlink(file);
	ft_free(number);
	ft_free(file);
}

// We make all our commandos free
void ft_free_comand(t_state *state)
{
	int i = 0;
	int ii = 0;

	state->t_comands = (char **)ft_free_table(state->t_comands);
	i = 0;
	if (!state->cmds)
	{
		return;
	}
	while (i < state->cmd_nmbs)
	{
		ii = 0;
		while (state->cmds[i].cmd_args && state->cmds[i].cmd_args[ii])
		{
			ft_free(state->cmds[i].cmd_args[ii]);
			ii++;
		}
		ft_delete_herodoc(&state->cmds[i]);
		ft_free(state->cmds[i].cmd_args);
		ft_free(state->cmds[i].cmd);
		ii = 0;
		while (state->cmds[i].t_redirection[ii])
		{
			ft_free(state->cmds[i].t_redirection[ii]);
			ii++;
		}
		ft_free(state->cmds[i].t_redirection);
		// ft_free_table(state->cmds[i].t_redirection);
		if (state->cmds[i].file > 0 )
		{
			close(state->cmds[i].file);
		}
		i++;
	}
	state->cmds = ft_free(state->cmds);
}

void	ft_check_exit(t_state	*state)
{
	ft_close_fd();
	ft_free_all(state);
}

// free to everything
void ft_free_all(t_state *state)
{
	state->cmd_paths = (char **)ft_free_table(state->cmd_paths);
	ft_free_comand(state);
	ft_free_table(state->t_redirection);
	state->fork_error = 0;
}
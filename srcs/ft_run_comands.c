/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_comands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:15:00 by dluna-lo          #+#    #+#             */
/*   Updated: 2022/12/22 14:33:15 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// The global variable that stores environment variables
char	**g_env;

// This function is in charge of finding the PATH variable, and returning its value, if there is an error it puts it in the global variable
char	*ft_find_path(char **envp, t_state *state)
{
	int	i;

	i = 0;
	while (ft_strncmp("PATH", envp[i], 4))
	{
		i++;
	}
	if (!envp[i])
	{
		printf("Error en PATH");
		state->error = 1;
		return (NULL);
	}
	return (envp[i] + 5);
}

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

void	ft_pipe_close(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->pipe_nmbs)
	{
		close(state->pipe[i]);
		i++;
	}
}

// Returns the number of commands sent.
int ft_number_comands(char *line)
{
	int ii = 0;
	int i = 0;
	char **table;

	if (ft_strlen(line) < 1)
	{
		return (0);
	}
	table = ft_split(line, '|');
	while (table[i])
	{
		i++;
	}
	while (table[ii])
	{
		free(table[ii]);
		ii++;
	}
	free(table);
	return (i);
}

void	ft_create_pipes(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->cmd_nmbs - 1)
	{
		if (pipe(state->pipe + 2 * i) < 0)
		{
			printf("Error in pipe");
			state->error = 1;
			return ;
		}
		i++;
	}
}

// Function for debug, which shows us all the created commands and their information.
void ft_print_cmds(t_state *state)
{
	int i = 0 ;
	int ii = 0;

	printf("\n ft_print_cmds \n");
	while (i < state->cmd_nmbs)
	{
		printf("id{%i} cmd{%s} ", state->cmds[i].id, state->cmds[i].cmd);
		ii = 0;
		while (state->cmds[i].cmd_args[ii])
		{
			printf("cmd_args{%s} ", state->cmds[i].cmd_args[ii]);
			ii++;
		}
		printf("\n");
		i++;
	}
}

// We make all our commandos free
void ft_free_comand(t_state *state)
{
	int i = 0 ;
	int ii = 0 ;

	while (state->t_comands[i])
	{
		free(state->t_comands[i]);
		i++;
	}
	free(state->t_comands);
	i = 0;
	while (i < state->cmd_nmbs)
	{
		ii = 0;
		while (state->cmds[i].cmd_args[ii])
		{
			free(state->cmds[i].cmd_args[ii]);
			ii++;
		}
		free(state->cmds[i].cmd_args);
		free(state->cmds[i].cmd);
		i++;
	}
	free(state->cmds);
}

// free to everything
void ft_free_all(t_state *state)
{
	int i = 0 ;
	int ii = 0 ;

	while (state->cmd_paths[i])
	{
		free(state->cmd_paths[i]);
		i++;
	}
	free(state->cmd_paths);
	ft_free_comand(state);
}

// This function creates a child process where the command sent will be executed.
void ft_process_comand(t_state	*state)
{
	state->pid = fork();
	if (state->pid == 0)
	{
		execve(state->cmds[0].cmd, state->cmds[0].cmd_args, g_env);
		printf("final Error comando : %s\n", state->cmds[0].cmd_args[0]);
	}
	else
	{
		waitpid(state->pid, NULL, 0);
	}
}

// we change from the output, input
void	ft_on_dup2(int zero, int one)
{
	dup2(zero, STDIN_FILENO);
	dup2(one, STDOUT_FILENO);
}

// Functions to run more than one, command with pipes.
void ft_process_comands(t_state	*state)
{
	state->pipe_nmbs = 2 * (state->cmd_nmbs - 1);
	state->pipe = (int *)malloc(sizeof(int) * state->pipe_nmbs);
	if (!state->pipe)
	{
		printf("Error en Pipe");
		state->error = 1;
	}
	ft_create_pipes(state);
	state->index = 0;
	while (state->index < state->cmd_nmbs && state->error == 0)
	{
		state->pid = fork();
		if (state->pid == 0)
		{
			if (state->index == 0)
			{
				ft_on_dup2(STDIN_FILENO, state->pipe[1]);
			}
			else if (state->index == state->cmd_nmbs - 1)
			{
				ft_on_dup2(state->pipe[2 * state->index - 2], STDOUT_FILENO);
			}
			else
			{
				ft_on_dup2(state->pipe[2 * state->index - 2], \
				state->pipe[2 * state->index + 1]);
			}
			ft_pipe_close(state);
			execve(state->cmds[state->index].cmd, state->cmds[state->index].cmd_args, g_env);
			printf("Error comando : cmd{%s} cmd_args{%s} -> \n", state->cmds[state->index].cmd, state->cmds[state->index].cmd_args[0]);
			exit(0);
		}
		state->index++;
	}
	waitpid(-1, NULL, 0);
	state->i++;
	if (state->i > 1)
	{
		int i = 1;
		while (i < state->cmd_nmbs)
		{
			waitpid(-1, NULL, 0);
			i++;
		}
		state->i = 2;
	}
	state->index = 0;
	ft_pipe_close(state);
	free(state->pipe);
}

// The command handler
void ft_run_comands(t_state	*state)
{
	state->save_stdout = dup(STDOUT_FILENO);
	state->save_stdin = dup(STDIN_FILENO);
	if (state->cmd_nmbs ==  1)
	{
		ft_process_comand(state);
		// state->i = 0 ;
	}
	else
	{
		ft_process_comands(state);
	}
	dup2(state->save_stdout, STDOUT_FILENO);
	dup2(state->save_stdin, STDIN_FILENO);
}

// We check the number of commands sent and create our array, with the information of each one
void	ft_minishell(t_state	*state, char *line)
{
	int i = 0;

	state->cmd_nmbs = ft_number_comands(line);
	if (state->cmd_nmbs > 0 )
	{
		state->env_path = ft_find_path(g_env, state);
		state->cmd_paths = ft_split(state->env_path, ':');
		state->cmds = ft_calloc(sizeof(t_cmd), state->cmd_nmbs);
		state->t_comands = ft_split(line, '|');
		while (i < state->cmd_nmbs)
		{
			state->cmds[i].id = i;
			state->cmds[i].cmd_args = ft_split(state->t_comands[i], ' ');
			state->cmds[i].cmd = ft_get_comand_p(state->cmd_paths, state->cmds[i].cmd_args[0]);
			if (!state->cmds[i].cmd)
			{
				printf("Error comand : %s\n", state->t_comands[i]);
				state->error = 1;
			}
			i++;
		}
		// ft_print_cmds(state);
		if (state->error == 1)
		{
			ft_free_all(state);
		}
		else
		{
			ft_run_comands(state);
			ft_free_all(state);
		}
	}
}

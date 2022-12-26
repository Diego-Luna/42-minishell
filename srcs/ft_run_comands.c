/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_comands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:15:00 by dluna-lo          #+#    #+#             */
/*   Updated: 2022/12/26 18:37:12 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// The global variable that stores environment variables
char	**g_env;

// This function is in charge of finding the PATH variable, and returning its value, if there is an error it puts it in the global variable
char	*ft_find_env(char **envp, t_state *state, char *path)
{
	int	i;
	int	size;
	char **table;

	i = 0;
	size = ft_size_table(envp, 0);
	while (i < size && ft_strncmp(path, envp[i], ft_strlen(path)))
	{
		i++;
	}
	if (i == size)
	{
		table = ft_calloc(sizeof(char *), 1);
		table[0] = path;
		ft_error_message(M_ERROR_FIND_ENV, table, state, N_ERROR_FIND_ENV);
		ft_free(table);
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

// We close all our pipes
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
	int size;
	char **table;

	if (ft_strlen(line) < 1)
	{
		return (0);
	}
	table = ft_split(line, '|');
	size = ft_size_table(table, 0);
	ft_free_table(table);
	return (size);
}

// We create the number of pipes, necessary for communication between processes
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

	ft_free_table(state->t_comands);
	i = 0;
	while (i < state->cmd_nmbs)
	{
		ii = 0;
		while (state->cmds[i].cmd_args[ii])
		{
			ft_free(state->cmds[i].cmd_args[ii]);
			ii++;
		}
		ft_free(state->cmds[i].cmd_args);
		ft_free(state->cmds[i].cmd);
		i++;
	}
	ft_free(state->cmds);
}

// free to everything
void ft_free_all(t_state *state)
{
	int i = 0 ;
	int ii = 0 ;

	ft_free_table(state->cmd_paths);
	ft_free_comand(state);
	state->fork_error = 0;
}

// This function creates a child process where the command sent will be executed.
void ft_process_comand(t_state	*state)
{
	int error;
	state->index = 0;
	if (state->stop != 1)
	{
		state->pid = fork();
		if (state->pid == 0)
		{
			// error = execve(state->cmds[0].cmd, state->cmds[0].cmd_args, g_env);
			error = ft_execve(state);
			ft_error_message(M_ERROR_EXECVE, state->cmds[0].cmd_args, state, N_ERROR_EXECVE);
			exit(error);
		}
		else
		{
			waitpid(state->pid, &state->fork_error, 0);
		}
	}
}

// we change from the output, input
void	ft_on_dup2(int zero, int one)
{
	dup2(zero, STDIN_FILENO);
	dup2(one, STDOUT_FILENO);
}


// The equation of the children commands with the fork
void	ft_run_childs(t_state *state)
{
	int error;
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
			// error = execve(state->cmds[state->index].cmd, state->cmds[state->index].cmd_args, g_env);
			error = ft_execve(state);
			ft_error_message(M_ERROR_EXECVE_PIPES, state->cmds[state->index].cmd_args, state, N_ERROR_EXECVE_PIPES);
			exit(error);
		}
		state->index++;
	}
}

void	ft_wait_childs_exit(t_state	*state)
{
	state->stop--;
	if (state->stop == 1)
	{
		ft_free_all(state);
		exit(0);
	}
}

void ft_wait_childs(t_state	*state)
{
	waitpid(-1, &state->fork_error, 0);
	ft_wait_childs_exit(state);
	state->i_run_pipes++;
	if (state->i_run_pipes > 1)
	{
		int i = 1;
		while (i < state->cmd_nmbs)
		{
			waitpid(-1, &state->fork_error, 0);
			ft_wait_childs_exit(state);
			i++;
		}
		state->i_run_pipes = 2;
	}
	state->index = 0;
}

// Functions to run more than one, command with pipes.
void ft_process_comands(t_state	*state)
{
	state->pipe_nmbs = 2 * (state->cmd_nmbs - 1);
	state->pipe = (int *)malloc(sizeof(int) * state->pipe_nmbs);
	if (!state->pipe)
	{
		ft_error_message(M_ERROR_CREATE_PIPE, NULL, state, N_ERROR_CREATE_PIPE);
	}
	ft_create_pipes(state);
	state->index = 0;
	ft_run_when_is_no_error(state, ft_run_childs);
	ft_run_when_is_no_error(state, ft_wait_childs);
	ft_pipe_close(state);
	ft_free(state->pipe);
}

// The command handler
void ft_run_comands(t_state	*state)
{
	// state->save_stdout = dup(STDOUT_FILENO);
	// state->save_stdin = dup(STDIN_FILENO);
	state->index = 0;
	if (state->cmd_nmbs ==  1)
	{
		ft_process_comand(state);
	}
	else
	{
		ft_process_comands(state);
	}
	// dup2(state->save_stdout, STDOUT_FILENO);
	// dup2(state->save_stdin, STDIN_FILENO);
}

// It shows us the error, at the same time that it helps us to debug.
void ft_error_message(char *str, char **table, t_state *state, int error)
{
	int i = 0;

	if (state->debug == 1)
	{
		printf("Error number:%d ", error);
	}
	printf("%s", str);
	while (table && table[i])
	{
		printf(" %s", table[i]);
		i++;
	}
	if (i > 0)
	{
		printf("\n");
	}
	state->error = error;
}

// A function that allows us to run the next part of the code as long as there are no errors.
void	ft_run_when_is_no_error(t_state *state, void (*f)(t_state *state))
{
	if (state->error == NO_ERROR)
	{
		f(state);
	}else{
		return ;
	}
}

// It is in charge of creating the array of the commanded functions
void ft_create_command_array(t_state *state)
{
	int i = 0;
	state->cmd_paths = ft_split(state->env_path, ':');
	state->cmds = ft_calloc(sizeof(t_cmd), state->cmd_nmbs);
	state->t_comands = ft_split(state->line, '|');
	while (i < state->cmd_nmbs)
	{
		state->cmds[i].id = i;
		state->cmds[i].cmd_args = ft_split(state->t_comands[i], ' ');
		state->cmds[i].cmd = ft_get_comand_p(state->cmd_paths, state->cmds[i].cmd_args[0]);
		if (!state->cmds[i].cmd && ft_is_special_commands(state->cmds[i].cmd_args[0]) == 0)
		{
			ft_error_message(M_ERROR_PATH, state->t_comands, state, N_ERROR_PATH);
		}
		if (ft_is_special_commands(state->cmds[i].cmd_args[0]) == 7)
		{
			state->stop = i + 1;
		}
		i++;
	}
}

// We check the number of commands sent and create our array, with the information of each one
void	ft_minishell(t_state	*state, char *line)
{
	state->cmd_nmbs = ft_number_comands(line);
	state->line = line;
	if (state->cmd_nmbs > 0 )
	{
		state->env_path = ft_find_env(g_env, state, "PATH");
		ft_run_when_is_no_error(state, ft_create_command_array);
		ft_run_when_is_no_error(state, ft_run_comands);
		ft_free_all(state);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_comands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:15:00 by dluna-lo          #+#    #+#             */
/*   Updated: 2022/12/30 18:34:00 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// The global variable that stores environment variables
extern char	**g_env;

// This function is in charge of finding the PATH variable, and returning its value, if there is an error it puts it in the global variable
char	*ft_find_env(char **envp, t_state *state, char *path)
{
	int	i;
	int	size;

	i = 0;
	size = ft_size_table(envp);
	while (i < size && ft_strncmp(path, envp[i], ft_strlen(path)))
	{
		i++;
	}
	if (i == size)
	{
		// ft_error_message(M_ERROR_FIND_ENV, NULL, state, N_ERROR_FIND_ENV);
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
	size = ft_size_table(table);
	ft_free_table(table);
	return (size);
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

	state->t_comands = (char **)ft_free_table(state->t_comands);
	i = 0;
	if (!state->cmds)
	{
		return;
	}
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
	state->cmds = ft_free(state->cmds);
}

// free to everything
void ft_free_all(t_state *state)
{
	int i = 0 ;
	int ii = 0 ;

	state->cmd_paths = (char **)ft_free_table(state->cmd_paths);
	ft_free_comand(state);
	state->fork_error = 0;
}

// falta
void	ft_process_comand_fork(t_state *state)
{
	int error;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		error = ft_execve(state);
		ft_error_message(M_ERROR_EXECVE, state->cmds[0].cmd_args, state, N_ERROR_EXECVE);
		exit(error);
	}
	else
	{
		waitpid(pid, &state->fork_error, 0);
	}
}

// This function creates a child process where the command sent will be executed.
void ft_process_comand(t_state	*state)
{
	state->index = 0;
	if (state->stop != STOP)
	{
		ft_run_unset_export(state);
		ft_run_when_is_no_error(state, ft_process_comand_fork);
	}
}

// The equation of the children commands with the fork
void	ft_run_childs(t_state *state)
{
	int error;

	error = 0;
	state->index = 0;
	while (state->index < state->cmd_nmbs && state->error == 0)
	{
		int		fd[2];

		pipe(fd);
		if (ft_wait_childs_exit(state) == 1)
		{
			ft_run_unset_export(state);
			if (state->error == NO_ERROR)
			{
				state->pid[state->index] = fork();
				if (state->pid[state->index] == 0)
				{
					if (state->index < state->cmd_nmbs - 1)
					{
						close(fd[0]);
						dup2(fd[1], STDOUT_FILENO);
					}
					error = ft_execve(state);
					ft_error_message(M_ERROR_EXECVE_PIPES, state->cmds[state->index].cmd_args, state, N_ERROR_EXECVE_PIPES);
					exit(error);
				}
				else if (state->index < state->cmd_nmbs)
				{
					close(fd[1]);
					dup2(fd[0], STDIN_FILENO);
				}
			}
		}
		state->index++;
	}
}

// It is in charge of checking when an exit is used, with the pipes, if there is one we save the number of the command and return 0, if not 1
int	ft_wait_childs_exit(t_state	*state)
{
	if (state->stop > STOP)
	{
		state->stop--;
	}
	if (state->stop == STOP)
	{
		state->pipe_stop = state->index + 1;
		state->stop = NO_STOP;
	}
	if (state->stop == NO_ERROR)
	{
		return (1);
	}
	return (0);
}

void ft_wait_childs(t_state	*state)
{
	state->index = 0;
	if (state->pipe_stop == -1)
	{
		while (state->index < state->cmd_nmbs)
		{
			waitpid(state->pid[state->index], &state->fork_error, 0);
			state->index++;
		}
	}else{
		while (state->pipe_stop != 0)
		{
			waitpid(state->pid[state->index], &state->fork_error, 0);
			state->index++;
			state->pipe_stop--;
		}
		exit(100);
	}
}

// Functions to run more than one, command with pipes.
void ft_process_comands(t_state	*state)
{
	pid_t	pid;

	state->pid = ft_calloc(sizeof(pid_t), state->cmd_nmbs);
	if (!state->pid)
	{
		ft_error_message(M_ERROR_CREATE_PIPE, NULL, state, N_ERROR_CREATE_PIPE);
	}
	state->index = 0;
	ft_run_when_is_no_error(state, ft_run_childs);
	ft_run_when_is_no_error(state, ft_wait_childs);
	if (state->error == 25600)
	{
		state->stop = STOP;
	}
	ft_free(state->pid);
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
	printf("\n");
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
	state->env_path = ft_find_env(g_env, state, "PATH");
	state->cmd_paths = ft_split(state->env_path, ':');
	state->cmds = ft_calloc(sizeof(t_cmd), state->cmd_nmbs);
	state->t_comands = ft_split(state->line, '|');
	while (i < state->cmd_nmbs)
	{
		state->cmds[i].id = i;
		state->cmds[i].cmd_args = ft_split(state->t_comands[i], ' ');
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
		ft_run_when_is_no_error(state, ft_create_command_array);
		ft_run_when_is_no_error(state, ft_run_comands);
		ft_free_all(state);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_comands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrembla <mtrembla@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:15:00 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/19 16:26:49 by mtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// The global variable that stores environment variables
// extern char	**g_env;

// This function is in charge of finding the PATH variable, and returning its value, if there is an error it puts it in the global variable
char	*ft_find_env(char **envp, char *path)
{
	int	i;
	int	ii;
	int	size;

	i = 0;
	size = ft_size_table(envp);
	ii = ft_strlen(path);
	while (i < size && ft_strncmp(path, envp[i], ii))
	{
		i++;
	}
	if (i == size)
	{
		return (NULL);
	}
	// return (envp[i] + 5);
	return (envp[i] + ii);
}

int	ft_find_env_index(char **envp, char *path)
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
		return (-1);
	}
	return (i);
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
	int iii = 0;

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
		iii = 0;
		while (state->cmds[i].t_redirection[iii])
		{
			printf("t_redirection{%s} ", state->cmds[i].t_redirection[iii]);
			iii++;
		}
		
		printf("\n");
		i++;
	}
}

// Command process with flork, for a single command, the child process executes the command and the parent waits until it has finished.
void	ft_process_comand_fork(t_state *state)
{
	int error;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_fork_signal();
		error = ft_execve(state);
		ft_error_message(M_ERROR_EXECVE, state->cmds[0].cmd_args, state, N_ERROR_EXECVE);
		exit(error);
	}
	else
		waitpid(pid, &state->fork_error, 0);
}

// This function creates a child process where the command sent will be executed.
void ft_process_comand(t_state	*state)
{
	state->index = 0;
	if (state->stop != STOP)
	{
		ft_on_redirection(state);
		if (ft_run_comand_build(state) == 0)
		{
			ft_run_when_is_no_error(state, ft_process_comand_fork);
		}
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
		state->pid[state->index] = fork();
		if (state->pid[state->index] == 0)
		{
			ft_fork_signal();
			if (state->index < state->cmd_nmbs - 1)
			{
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
			}
			ft_on_redirection(state);
			if (ft_run_comand_build(state) == 0)
			{
				error = ft_execve(state);
				ft_error_message(M_ERROR_EXECVE_PIPES, state->cmds[state->index].cmd_args, state, N_ERROR_EXECVE_PIPES);
			}
			ft_close_fd();
			exit(error);
		}
		else if (state->index < state->cmd_nmbs)
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
		}
		state->index++;
	}
}

void ft_wait_childs(t_state	*state)
{
	state->index = 0;
	while (state->index < state->cmd_nmbs)
	{
		waitpid(state->pid[state->index], &state->fork_error, 0);
		state->index++;
	}
}

// Functions to run more than one, command with pipes.
void ft_process_comands(t_state	*state)
{
	state->pid = ft_calloc(sizeof(pid_t), state->cmd_nmbs);
	if (!state->pid)
	{
		ft_error_message(M_ERROR_CREATE_PIPE, NULL, state, N_ERROR_CREATE_PIPE);
	}
	state->index = 0;
	ft_run_when_is_no_error(state, ft_run_childs);
	ft_run_when_is_no_error(state, ft_wait_childs);
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
	close(state->save_stdin);
	close(state->save_stdout);
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

int	ft_str_in_str(char *str, char *find)
{
	int i = 0;
	int i_save = 0;
	int ii = 0;
	// int size;

	if (!find)
	{
		return(-1);
	}
	// size = ft_strlen(find);
	while (str[i])
	{
		ii = 0;
		i_save = i;
		while (find[ii] && str[i] == find[ii])
		{
			if (!find[ii + 1] && find[ii] != str[i + 1])
			{
				return (i_save);
			}
			ii++;
			i++;
		}
		i = i_save;
		i++;
	}
	return (-1);
}

void ft_create_t_redirection(t_state *state)
{
	state->t_redirection = ft_calloc(sizeof(char *), 5);
	state->t_redirection[0] =  ft_strdup("<");
	state->t_redirection[1] =  ft_strdup(">");
	state->t_redirection[2] =  ft_strdup("<<");
	state->t_redirection[3] =  ft_strdup(">>");
	state->t_redirection[4] =  0;
}

void ft_save_type_redirection(t_state *state, int i)
{
	int ii;

	ii = 4;
	while (ii >= 0)
	{
		if (ft_str_in_str(state->t_comands[i], state->t_redirection[ii]) >= 0)
		{
			state->cmds[i].redirect = ii;
			break;
		}
		ii--;
	}
}

int ft_position_in_token(t_tokens l, char *str, int n_pipe)
{
	int i = 0;
	int pipe = 0;
	t_node	*aff;

	aff = l.first;
	while (aff)
	{
		if (ft_strncmp(aff->content, "|", 2) == 0)
		{
			pipe++;
		}
		else if ( pipe == n_pipe && ft_strncmp(aff->content, str, ft_strlen(aff->content)) == 0)
		{
			return (i);
		}
		i++;
		aff = aff->next;
	}
	return (-1);
}

char *ft_get_char_node(t_tokens l, int position)
{
	int i;
	t_node	*aff;

	i = 0;
	aff = l.first;
	while (aff)
	{
		if ( position == i)
		{
			return (aff->content);
		}
		i++;
		aff = aff->next;
	}
	return (NULL);
}

void	ft_cmd_args_in_redirection(t_state *state, int i)
{
	int ii = 0;
	int iii = 0;
	int position_redi = 0;
	int	size_copy = 0;
	char	**new;
	t_cmd *cmd;

	state->cmds[i].t_redirection = ft_calloc(sizeof(char *), 2);
	cmd = &state->cmds[i];
	position_redi = ft_position_in_token(*state->tokens, state->t_redirection[cmd->redirect], i);
	if (position_redi >= ft_tokens_size(*state->tokens) - 2)
	{
		state->cmds[i].cmd_args = NULL;
		ft_error_message(M_ERROR_TOKENS_REDE, NULL, state, N_ERROR_TOKENS_REDE);
		return;
	}
	position_redi++;
	state->cmds[i].t_redirection[0] = ft_strdup(ft_get_char_node(*state->tokens, position_redi));
	state->cmds[i].cmd_args = ft_content_tokens(state, i, *state->tokens);
	size_copy = ft_size_table(state->cmds[i].cmd_args);
	new = ft_calloc( sizeof(char *), size_copy);
	position_redi = 0;
	while (ii < size_copy)
	{
		if (ft_strncmp(state->t_redirection[cmd->redirect], state->cmds[i].cmd_args[ii], ft_strlen(state->cmds[i].cmd_args[ii])) == 0)
		{
			position_redi = 1;
			ii++;
		}
		else
		{
			new[iii] = ft_strdup(state->cmds[i].cmd_args[ii]);
			iii++;
		}
		ii++;
	}
	state->cmds[i].cmd_args = (char **)ft_free_table(state->cmds[i].cmd_args);
	state->cmds[i].cmd_args = new;
}

int ft_tokens_size(t_tokens l)
{
	t_node	*aff;
	int i = 1;

	aff = l.first;
	while (aff)
	{
		i++;
		aff = aff->next;
	}
	return (i);
}

char **ft_content_tokens(t_state *state, int number_pipe, t_tokens l)
{
	char **table;
	t_node	*aff;
	int i = 0;
	int pipe = 0;

	aff = l.first;
	if (state->cmd_nmbs == 1)
	{
		while (aff)
		{
			i++;
			aff = aff->next;
		}
	}
	else
	{
		while (aff)
		{
			if (ft_strncmp(aff->content, "|\0", 2) == 0)
			{
				pipe++;
			}
			else if (pipe > number_pipe)
			{
				break;
			}
			else if (pipe == number_pipe)
			{
				i++;
			}
			aff = aff->next;
		}
	}
	table = ft_calloc(sizeof(char *), i + 1);
	aff = l.first;
	pipe = 0;
	i = 0;
	if (state->cmd_nmbs == 1 )
	{
		while (aff)
		{
			table[i] = ft_strdup(aff->content);
			aff = aff->next;
			i++;
		}
	}
	else
	{
		while (aff)
		{
			if (ft_strncmp(aff->content, "|\0", 2) == 0)
			{
				pipe++;
			}
			else if (pipe > number_pipe)
			{
				break;
			}
			else if (pipe == number_pipe)
			{
				table[i] = ft_strdup(aff->content);
				i++;
			}
			aff = aff->next;
		}
	}
	return (table);
}

char *ft_save_token(t_state *state, int number_pipe)
{
	char *save;
	t_node	*aff;
	int i = 0;
	int pipe = 0;
	int size = 0;

	aff = state->tokens->first;
	if (state->cmd_nmbs == 1)
	{
		while (aff)
		{
			i++;
			size += ft_strlen(aff->content) + 1;
			aff = aff->next;
		}
	}
	else
	{
		while (aff)
		{
			if (ft_strncmp(aff->content, "|\0", 2) == 0)
			{
				pipe++;
			}
			else if (pipe > number_pipe)
			{
				break;
			}
			else if (pipe == number_pipe)
			{
				size += ft_strlen(aff->content);
				i++;
				if (aff->next && ft_strncmp(aff->next->content, "|\0", 2) != 0)
				{
					size++;
				}
			}
			aff = aff->next;
		}
	}
	size++;
	save = ft_calloc(sizeof(char), size);
	aff = state->tokens->first;
	i = 0;
	pipe = 0;
	if (state->cmd_nmbs == 1)
	{
		while (aff)
		{
			ft_strlcat(save, aff->content, size + 1);
			aff = aff->next;
			if (aff)
			{
				ft_strlcat(save, " ", size + 1);
			}
		}
	}
	else
	{
		while (aff)
		{
			if (ft_strncmp(aff->content, "|\0", 2) == 0)
			{
				pipe++;
			}
			else if (pipe > number_pipe)
			{
				break;
			}
			else if (pipe == number_pipe)
			{
				ft_strlcat(save, aff->content, size);
				// ft_strlcat(save, aff->content, size + 1);
				i++;
				if (aff->next)
				{
					ft_strlcat(save, " ", 1);
				}
			}
			aff = aff->next;
		}
	}
	return (save);
}

char **ft_table_token(t_state *state)
{
	int i = 0;
	char **table;

	table = ft_calloc(sizeof(char *),  state->cmd_nmbs + 1);
	while (i < state->cmd_nmbs)
	{
		table[i] = ft_save_token(state, i);
		i++;
	}

	return (table);
}

// It is in charge of creating the array of the commanded functions
void ft_create_command_array(t_state *state)
{
	(void)state;
	int i = 0;

	ft_create_t_redirection(state);
	state->cmds = ft_calloc(sizeof(t_cmd), state->cmd_nmbs + 1);
	state->t_comands = ft_table_token(state);
	while (i < state->cmd_nmbs)
	{
		state->cmds[i].id = i;
		state->cmds[i].redirect = -1;
		state->cmds[i].file = -1;
		ft_save_type_redirection(state, i);
		if (state->cmds[i].redirect >= 0)
		{
			ft_cmd_args_in_redirection(state, i);
		}
		else
		{
			state->cmds[i].t_redirection = ft_calloc(sizeof(char *), 1);
			state->cmds[i].cmd_args = ft_content_tokens(state, i, *state->tokens);
		}
		i++;
	}
}

int ft_str_is_a_number(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

// char *ft_cur_str(char *str)
// {
// 	int i = 0;
// 	int ii = 0;
// 	char *new;

// 	while (str[i] && !(str[i] == ' ' || str[i] == '\t' || str[i] == '\''  || str[i] == '\"'))
// 	{
// 		i++;
// 	}
// 	new = ft_calloc(sizeof(char), i + 1);


// }

void ft_handle_env_varibles(t_state *state, int i, int ii)
{
	t_cmd *cmd;

	cmd = &state->cmds[i];
	char *path_clean;
	char *path;

	// if (cmd->cmd_args[ii][0] == '$' && ft_strlen(cmd->cmd_args[ii]) > 1)
	if (ft_strchr_get(cmd->cmd_args[ii], '$') >= 0 && ft_strlen(cmd->cmd_args[ii]) > (size_t)ft_strchr_get(cmd->cmd_args[ii], '$')  && ft_strlen(cmd->cmd_args[ii]) > 1)
	{
		path_clean = ft_clean_str(ft_strchr(cmd->cmd_args[ii], '$') + 1);
		path = ft_strjoin(path_clean, "=");
		if (ft_find_env(state->g_env, path) != NULL)
		{
			cmd->cmd_args[ii] = ft_free(cmd->cmd_args[ii]);
			cmd->cmd_args[ii] = ft_calloc(sizeof(char), ft_strlen(ft_find_env(state->g_env, path)) + 1);
			ft_strlcat(cmd->cmd_args[ii], ft_find_env(state->g_env, path), ft_strlen(ft_find_env(state->g_env, path)) + 1);
		}
		else if (ii > 0)
		{
			cmd->cmd_args[ii] = ft_free(cmd->cmd_args[ii]);
		}
		ft_free(path);
		ft_free(path_clean);
	}
}

void ft_add_info_comands(t_state *state)
{
	int i = 0;
	int ii = 0;
	int modife = 1;
	t_cmd *cmd;
	char *path;

	while (i < state->cmd_nmbs)
	{
		cmd = &state->cmds[i];
		ii = 0;
		while (cmd->cmd_args[ii])
		{
			if (cmd->cmd_args[ii][0] == '\'')
			{
				modife = 0;
			}
			cmd->cmd_args[ii] = ft_clean_quotes(cmd->cmd_args[ii]);
			path = ft_clean_space_str(cmd->cmd_args[ii]);
			cmd->cmd_args[ii] = ft_free(cmd->cmd_args[ii]);
			cmd->cmd_args[ii] = path;
			if (modife == 1)
			{
				ft_handle_env_varibles(state, i, ii);
			}
			ii++;
		}
		ii = 0;
		while (cmd->t_redirection && cmd->t_redirection[ii])
		{
			cmd->t_redirection[ii] = ft_clean_quotes(cmd->t_redirection[ii]);
			ii++;
		}
		if (cmd->redirect == 1)
		{
			state->index = i;
			ft_redirection_two(state, 0);
		}
		if (cmd->redirect == 3)
		{
			state->index = i;
			ft_redirection_four(state, 0);
		}
		if (cmd->redirect == 2)
		{
			ft_create_herodoc_(state, i);
		}
		i++;
	}
}

int ft_number_comands_parsing(t_tokens tokens)
{
	t_node	*aff;
	int i = 1;

	aff = tokens.first;
	while (aff)
	{
		if (ft_strncmp(aff->content, "|\0", 2) == 0)
		{
			i++;
		}
		aff = aff->next;
	}
	return (i);
}

// We check the number of commands sent and create our array, with the information of each one
void	ft_minishell(t_state	*state, char *line, t_tokens *tokens)
{
	// state->cmd_nmbs = ft_number_comands(line);
	state->cmd_nmbs = ft_number_comands_parsing(*tokens);
	state->line = line;
	if (state->cmd_nmbs > 0 && state->error == NO_ERROR)
	{
		state->tokens = NULL;
		state->tokens = tokens;
		ft_run_when_is_no_error(state, ft_create_command_array);
		ft_run_when_is_no_error(state, ft_add_info_comands);
		// ft_print_cmds(state);
		ft_run_when_is_no_error(state, ft_run_comands);
		ft_handle_error_pipe(state);
		ft_check_exit(state);
	}
}

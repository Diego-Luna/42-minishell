/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:42:51 by dluna-lo          #+#    #+#             */
/*   Updated: 2022/12/26 18:11:57 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
#include <signal.h>
#include <termios.h>
#include "./readline/readline.h"
#include "./readline/history.h"

// Error control,
// N is the number and M is the message
# define STOP 1
# define NO_STOP 0

# define ERROR 1
# define NO_ERROR 0

# define M_ERROR_PATH "Error comand :"
# define N_ERROR_PATH 1
# define M_ERROR_EXECVE "Error comando :"
# define N_ERROR_EXECVE 2
# define M_ERROR_FIND_ENV "It was not found :"
# define N_ERROR_FIND_ENV 3
# define M_ERROR_CREATE_PIPE "Error creating pipe"
# define N_ERROR_CREATE_PIPE 4
# define M_ERROR_EXECVE_PIPES "Error creating pipe"
# define N_ERROR_EXECVE_PIPES 5
// Error control


// array comands
typedef struct va_t_cmd
{
	int 	id;
	char	**cmd_args;
	char	*cmd;
	pid_t	pid;
}			t_cmd;

typedef struct va_states
{
	char	**t_comands;
	char	*env_path;
	char	*line;
	char	**cmd_paths;
	pid_t	pid;
	int 	*pipe;
	int		cmd_nmbs;
	int		pipe_nmbs;
	int		index;
	int		error;
	int		fork_error;
	int		stop;
	int		debug;
	int		save_stdout;
	int		save_stdin;
	int		i_run_pipes;
	t_cmd *cmds;
}			t_state;

//signals
void	ft_signals();
void    ft_disable_echo(void);
void	ft_sigint_handler();


// run comands, and pipe
char	*ft_find_env(char **envp, t_state *state, char *path);
void	ft_childs(t_state state, char **envp, char *argv);
void	ft_minishell(t_state	*state, char *line);

// ENV
char	**ft_crate_env(char **old, int size, int f);

// tables
int	ft_size_table(char **array, int add);

// free
void	*ft_free(void *ptr);
void	**ft_free_table(char **array);

// Error
void ft_error_message(char *str, char **table, t_state *state, int error);
void	ft_run_when_is_no_error(t_state *state, void (*f)(t_state *state));

// special_commands
int ft_is_special_commands(char	*comand);
int ft_execve(t_state *state);

#endif
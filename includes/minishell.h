/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:42:51 by dluna-lo          #+#    #+#             */
/*   Updated: 2022/12/22 14:16:28 by dluna-lo         ###   ########.fr       */
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
	int		infile;
	int		outfile;
	char	**envp;
	char	**t_comands;
	char	*env_path;
	char	**cmd_paths;
	pid_t	pid;
	pid_t	*pids;
	int 	*pipe;
	int		cmd_nmbs;
	int		pipe_nmbs;
	int		index;
	int		error;
	int		stop;
	int		save_stdout;
	int		save_stdin;
	int		i;
	t_cmd *cmds;
}			t_state;

//signals
void	ft_signals();
void    ft_disable_echo(void);
void	ft_sigint_handler();


// run comands, and pipe
char	*ft_find_path(char **envp, t_state *state);
void	ft_childs(t_state state, char **envp, char *argv);
void	ft_minishell(t_state	*state, char *line);


#endif
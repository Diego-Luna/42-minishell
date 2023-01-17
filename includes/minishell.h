/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrembla <mtrembla@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:42:51 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/17 16:03:48 by mtrembla         ###   ########.fr       */
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

typedef struct s_node
{
	char			*content;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_tokens
{
	t_node	*first;
	t_node	*last;
}	t_tokens;

//signals
void	ft_signals();
void    ft_disable_echo(void);
void	ft_sigint_handler();

//dlist
void	dlist_add_back(t_tokens *l, char *elem);
void	dlist_remove_node(t_node *node);
void	dlist_free(t_tokens *l);
void	view(t_tokens l);

//parsing
void	ft_parse(char *line, t_tokens *tokens);
char	*ft_clean_quotes(char *old_str);
char	*ft_trim_char(char *str, int ptr);

//split
int		ft_splitable(char c);
void	ft_minishell_split(char *args, t_tokens *t);
int		ft_quotes(char *args, int i);
int		ft_create_token(char *args, int i, int start, t_tokens *t);

// run comands, and pipe
char	*ft_find_path(char **envp, t_state *state);
void	ft_childs(t_state state, char **envp, char *argv);
void	ft_minishell(t_state	*state, char *line);


#endif
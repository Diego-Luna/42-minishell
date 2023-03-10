/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:42:51 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/02/08 12:00:27 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include "./libft/libft.h"
# include "./readline/history.h"
# include "./readline/readline.h"

// Error control,
// N is the number and M is the message
# define STOP 1
# define NO_STOP 0

# define ERROR 1
# define NO_ERROR 0

# define M_ERROR_PATH "Error comand : "
# define N_ERROR_PATH 1
# define M_ERROR_EXECVE "Error comando : "
# define N_ERROR_EXECVE 2
# define M_ERROR_FIND_ENV "It was not found : "
# define N_ERROR_FIND_ENV 3
# define M_ERROR_CREATE_PIPE "Error creating pipe: "
# define N_ERROR_CREATE_PIPE 4
# define M_ERROR_EXECVE_PIPES "Error creating pipe: "
# define N_ERROR_EXECVE_PIPES 5
# define M_ERROR_UNSET_MISSING "Error in unset missing argument: "
# define N_ERROR_UNSET_MISSING 6
# define M_ERROR_UNSET_NOT_EXIST "Error in insert missing variable \
	does not exist: "
# define N_ERROR_UNSET_NOT_EXIST 7
# define M_ERROR_NUMERIC_ARGUMENTS "Numeric argument required: "
# define N_ERROR_NUMERIC_ARGUMENTS 8
# define M_ERROR_MANY_ARGUMENTS "many arguments: "
# define N_ERROR_MANY_ARGUMENTS 9
# define M_ERROR_NO_EXIST "No exits: "
# define N_ERROR_NO_EXIST 10
# define M_ERROR_NO_FILE_DIC "No such file or directory: "
# define N_ERROR_NO_FILE_DIC 11
# define M_ERROR_TOKENS_REDE "Syntax error near unexpected tokens: "
# define N_ERROR_TOKENS_REDE 12
# define M_ERROR_EXPORT "export: not a valid identifier: "
# define N_ERROR_EXPORT 13
# define M_ERROR_TOKEN "syntax error near unexpected token `|'"
# define N_ERROR_TOKEN 14
# define M_ERROR_TOKENS "syntax error near unexpected token `||'"
# define N_ERROR_TOKENS 15
// Error control

// array comands
typedef struct s_t_cmd
{
	int				id;
	char			**cmd_args;
	char			*cmd;
	char			**r_cmd_args;
	int				*redirect;
	int				n_of_redi;
	int				i_redi;
	char			*s_redirection;
	char			**t_redirection;
	int				file;
}					t_cmd;

typedef struct s_node
{
	char			*content;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

typedef struct s_tokens
{
	t_node			*first;
	t_node			*last;
	int				error;
}					t_tokens;

typedef struct s_states
{
	char			**t_redirection;
	char			**t_comands;
	char			**cmd_paths;
	char			**g_env;
	t_tokens		*tokens;
	char			*env_path;
	char			*line;
	t_cmd			*cmds;
	pid_t			*pid;
	int				save_stdout;
	int				save_stdin;
	int				fork_error;
	int				pipe_stop;
	int				cmd_nmbs;
	int				index;
	int				stop_pipes;
	int				error;
	int				debug;
	int				stop;
	int				exit;
}					t_state;

void				ft_reable_echo(void);
// --> signals
void				ft_signals(void);
void				ft_disable_echo(void);
void				ft_fork_handler(int signum);
void				ft_sigint_handler(int signum);
void				ft_fork_signal(void);

//dlist
void				dlist_add_back(t_tokens *l, char *elem);
void				dlist_remove_node(t_node *node);
void				dlist_free(t_tokens *l);
void				view(t_tokens l);

//parsing
void				ft_parse(char *line, t_tokens *tokens, t_state *state);
char				*ft_clean_quotes(char *old_str);
char				*ft_trim_char(char *str, int ptr);
void				ft_repetition_check(t_tokens *t);
void				ft_init_tokens(t_tokens *tokens);

//split
int					ft_splitable(char c);
void				ft_minishell_split(char *args, t_tokens *t);
int					ft_quotes(char *args, int i, t_tokens *t);
int					ft_create_token(char *args, int i, int start, t_tokens *t);

// --> ft_minishell
void				ft_init_state(t_state *state, char **envp);
void				ft_minishell(t_state *state, char *line, t_tokens *tokens);
void				ft_create_command_array(t_state *state);
void				ft_add_info_comands(t_state *state);
void				ft_run_comands(t_state *state);
void				ft_handle_error_pipe(t_state *state);
void				ft_check_exit(t_state *state);
void				ft_check_pipes(t_state *state);

// --> ft_run_comands
void				ft_process_comand(t_state *state);
void				ft_process_comands(t_state *state);
void				ft_childs(t_state state, char **envp, char *argv);
void				ft_run_childs(t_state *state);

//  --> ft_create_command_array
void				ft_cmd_args_in_redirection(t_state *state, int i);
char				**ft_content_tokens(t_state *state, int number_pipe,
						t_tokens l);
char				*ft_save_token(t_state *state, int number_pipe);
int					ft_position_in_token(t_tokens l, char *str, int n_pipe,
						int *start);
char				*ft_get_char_node(t_tokens l, int position);
int					ft_tokens_size(t_tokens l);
void				ft_create_t_redirection(t_state *state);
char				**ft_cmd_args_in_redirection_create(t_state *state,
						char **tem, t_cmd *cmd, int size_copy);
int					ft_save_type_redirection_while(t_state *state, t_node *aff,
						int i);
int					ft_save_type_redirection(t_state *state, int i);
char				**ft_table_token(t_state *state);

// --> ENV
char				**ft_crate_env(char **old, int size, int f);
char				*ft_get_comand_p(char **paths, char *cmd);
int					ft_find_env_index(char **envp, char *path);
char				*ft_find_env(char **envp, char *path);

// --> tables
int					ft_size_table(char **array);

// --> free
void				*ft_free(void *ptr);
void				**ft_free_table(char **array);
void				ft_close_fd(void);
void				ft_free_all(t_state *state);

// --> Error
void				ft_error_message(char *str, char **table, t_state *state,
						int error);
void				ft_run_when_is_no_error(t_state *state,
						void (*f)(t_state *state));

// --> special_commands
// controler
int					ft_run_comand_build(t_state *state);

int					ft_execve(t_state *state);
int					ft_delate_env(t_state *state, char **env_name);
int					ft_add_env(t_state *state, char **past, int check);
void				ft_env_export(t_state *state, char *str, int check);

// --> redirection
char				**ft_content_tokens(t_state *state, int number_pipe,
						t_tokens l);
int					ft_on_redirection(t_state *state);
void				ft_create_herodoc(t_state *state, int index);
void				ft_redirection_two(t_state *state, int is_dup2);
void				ft_redirection_four(t_state *state, int is_dup2);

// str
char				*ft_clean_space_str(char *str);
char				*ft_clean_str(char *str);
int					ft_strchr_get(const char *s, int c);
void				ft_str_to_str(char *dst, char *src);
char				*ft_only_str_isalnum(char *str);
int					ft_str_in_str(char *str, char *find);

// --> add_info_comand
char				*ft_modif(char *cmd_args, char **env, int ii);
int					ft_is_delete(t_state *state, int *num, char *tem);
int					ft_handle_env_varibles_if(t_state *state, int i, int ii);
char				*ft_handle_env_varibles_utils(t_state *state, int *num,
						int ii, int i);

// --> tokens utils
int					ft_tokens_size(t_tokens l);

// --> debug
void				ft_print_table_debug(char **table);
void				ft_print_cmds(t_state *state);

// --> ft_run_comand_build
void				ft_comand_exit(t_state *state, char **run_comand);
void				ft_print_table(char **str, int new_line);
void				ft_echo(t_state *state);
void				ft_comand_pwd(t_state *state);
int					ft_is_only_char(char *str, int c);

void				ft_signal_stop(void);

#endif
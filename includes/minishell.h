/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrembla <mtrembla@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:42:51 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/08 18:32:18 by mtrembla         ###   ########.fr       */
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

typedef struct va_states
{
	int		i;
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
void	dlist_add_front(t_tokens *l, char *elem);
void	dlist_remove_node(t_node *node);
void	dlist_free(t_tokens *l);
void	view(t_tokens l);

//parsing
void	ft_parse(char *line, t_tokens *tokens);

//split
int		ft_splitable(char c);
void	ft_minishell_split(char *args, t_tokens *t);
void	ft_create_token(char *args, int start, int end, t_tokens *l);
char	*ft_strcpy(char *dest, char *src, int len);


#endif
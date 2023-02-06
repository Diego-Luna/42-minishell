/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:28:21 by mtrembla          #+#    #+#             */
/*   Updated: 2023/01/25 15:19:42 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
ft_disable_echo mute the usual outputs from signals by
taking terminal attributes and changing them.
signals are then redirected to their new fonction.
*/

void	ft_signals(void)
{
	ft_disable_echo();
	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_fork_signal(void)
{
	signal(SIGINT, ft_fork_handler);
	signal(SIGQUIT, SIG_DFL);
}

void	ft_disable_echo(void)
{
	struct termios	old;
	struct termios	new;

	tcgetattr(STDIN_FILENO, &old);
	new = old;
	new.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new);
}

void	ft_fork_handler(int signum)
{
	(void)signum;
}

void	ft_sigint_handler(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

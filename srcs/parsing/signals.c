/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegofranciscolunalopez <diegofrancisco    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:28:21 by mtrembla          #+#    #+#             */
/*   Updated: 2023/01/22 18:31:19 by diegofranci      ###   ########.fr       */
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

static void	ft_interupt(int signal)
{
	if (signal == SIGINT)
	{
		kill(0, 0);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
	}
	if (signal == SIGQUIT)
	{
		kill(0, 0);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
	}
}

void	ft_signal_stop(void)
{
	signal(SIGINT, ft_interupt);
	signal(SIGQUIT, ft_interupt);
}

//WARNING RESET BEFORE CLOSING!!!!!!!
void    ft_disable_echo(void)
{
	struct termios	attributes;

	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &attributes);
}

void ft_fork_handler(int signum)
{
	(void)signum;
}

void	ft_sigint_handler(void)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

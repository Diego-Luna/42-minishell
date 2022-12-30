/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:28:21 by mtrembla          #+#    #+#             */
/*   Updated: 2022/12/22 20:01:36 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// The global variable that stores environment variables
char	**g_env;

/*
ft_disable_echo mute the usual outputs from signals by
taking terminal attributes and changing them.
signals are then redirected to their new fonction.
*/

void	ft_signals()
{
	ft_disable_echo();
	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

//WARNING RESET BEFORE CLOSING!!!!!!!
void    ft_disable_echo(void)
{
    struct termios    attributes;

    tcgetattr(STDIN_FILENO, &attributes);
    attributes.c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &attributes);
}

void	ft_sigint_handler()
{
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrembla <mtrembla@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:28:21 by mtrembla          #+#    #+#             */
/*   Updated: 2023/01/16 10:53:12 by mtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	rl_replace_line("", 0);
	rl_redisplay();
}

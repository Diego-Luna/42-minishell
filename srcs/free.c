/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 10:47:26 by diegofranci       #+#    #+#             */
/*   Updated: 2023/01/18 15:28:02 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// The global variable that stores environment variables
extern char	**g_env;

void	ft_close_fd(void)
{
	int	i;

	i = 4;
	// while (i < 200)
	while (i < 101)
	{
		close(i);
		i++;
	}
}
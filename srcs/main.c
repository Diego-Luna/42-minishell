/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrembla <mtrembla@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:50:01 by dluna-lo          #+#    #+#             */
/*   Updated: 2022/12/21 11:29:27 by mtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_state	state;

	(void)argc;
	(void)argv;
	(void)envp;
	(void)state;
	
	char *line;

	ft_signals();
	while (1)
	{
    	line = readline("minishell$> ");
		if (!line)
			break;
		if (line && *line)
			add_history(line);
		free(line);	
	}
    return (0);
}

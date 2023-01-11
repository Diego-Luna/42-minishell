/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrembla <mtrembla@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:50:01 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/11 12:28:22 by mtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	// t_state		state;
	t_tokens	tokens;

	(void)argc;
	(void)argv;
	(void)envp;
	// state.i = 1;
	
	char *line;

	ft_signals();
	while (1)
	{
    	line = readline("minishell$> ");
		if (line && *line)
			add_history(line);
		if (!line)
			break;
		ft_parse(line, &tokens);
		free(line);	
	}
	rl_clear_history();
    return (0);
}

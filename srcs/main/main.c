/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:50:01 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/24 12:53:24 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_state		state;
	t_tokens	tokens;
	char *line;

	(void)argc;
	(void)argv;
	state.tokens = &tokens;
	ft_init_state(&state, envp);
	ft_signals();
	while (state.stop != STOP)
	{
    line = readline("minishell$> ");
		if (line && *line)
		{
			add_history(line);
			state.error = 0 ;
			ft_parse(line, &tokens, &state);
		}
		if (!line)
		{
			break;
		}
		free(line);
	}
	ft_free_table(state.g_env);
	rl_clear_history();
	exit(state.exit);
  return (0);
}

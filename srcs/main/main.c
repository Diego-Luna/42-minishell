/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:50:01 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/25 15:10:24 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_run_code(char *line, t_state *state, t_tokens	*tokens)
{
	add_history(line);
	state->error = 0;
	ft_parse(line, tokens, state);
}

int	main(int argc, char **argv, char **envp)
{
	t_state		state;
	t_tokens	tokens;
	char		*line;

	(void)argc;
	(void)argv;
	state.tokens = &tokens;
	ft_init_state(&state, envp);
	ft_signals();
	while (state.stop != STOP)
	{
		line = readline("minishell$> ");
		if (line && *line)
			ft_run_code(line, &state, &tokens);
		if (!line)
			break ;
		ft_free(line);
	}
	ft_free_table(state.g_env);
	rl_clear_history();
	exit(state.exit);
	return (0);
}

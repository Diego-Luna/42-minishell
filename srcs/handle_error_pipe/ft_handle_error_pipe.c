/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_error_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:51:11 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/25 15:06:50 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_handle_error_pipe(t_state *state)
{
	char	**tem_comand;
	char	*status;

	state->fork_error /= 256;
	if (state->fork_error == 9)
	{
		state->fork_error = 127;
	}
	status = ft_itoa(state->fork_error);
	tem_comand = calloc(sizeof(char *), 3);
	tem_comand[0] = ft_strdup("env");
	tem_comand[1] = ft_strjoin("?=", status);
	ft_add_env(state, tem_comand);
	ft_free(status);
	ft_free(tem_comand[0]);
	ft_free(tem_comand[1]);
	ft_free(tem_comand);
}

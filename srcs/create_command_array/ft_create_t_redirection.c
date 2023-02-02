/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_t_redirection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:55:28 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/02/02 11:56:54 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_create_t_redirection(t_state *state)
{
	state->t_redirection = ft_calloc(sizeof(char *), 5);
	state->t_redirection[0] = ft_strdup("<");
	state->t_redirection[1] = ft_strdup(">");
	state->t_redirection[2] = ft_strdup("<<");
	state->t_redirection[3] = ft_strdup(">>");
	state->t_redirection[4] = 0;
}

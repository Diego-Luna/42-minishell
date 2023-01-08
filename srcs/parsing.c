/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrembla <mtrembla@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:30:09 by mtrembla          #+#    #+#             */
/*   Updated: 2023/01/08 18:32:33 by mtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_parse(char *line, t_tokens *tokens)
{
	char *args;
	
	args = line;
	tokens = malloc(sizeof(t_tokens));
	ft_minishell_split(args, tokens);

}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrembla <mtrembla@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:30:09 by mtrembla          #+#    #+#             */
/*   Updated: 2022/12/21 14:56:48 by mtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_parse(char *line, t_tokens *tokens)
{
	char *args;
	
	args = line;
	tokens = malloc(sizeof(t_tokens));
	ft_create_tokens(args, tokens);

}

//space, chevron, pipe
void	ft_create_tokens(char *args, t_tokens *t)
{
	printf("args: %s\n", args);
	printf("%d\n", ft_number_of_tokens(args));
}

//check if all tokens are alphanum or $, else return token with error
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrembla <mtrembla@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:58:06 by mtrembla          #+#    #+#             */
/*   Updated: 2022/12/21 15:47:22 by mtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_splitable(char c)
{
	if (c == ' ' || c == '<' || c == '>' || c == '|')
		return(1);
	return(0);
}

int	ft_number_of_tokens(char *s)
{
	int i = 0;
	unsigned int	nb_of_tokens = 1;

	while(s[i])
	{
		if (ft_splitable(s[i]))
		{
			nb_of_tokens++;
			if(s[i] == s[i + 1])
				i++;
		}
		i++;
	}
	printf("%c\n", s[i-1]);
	if(ft_splitable(s[i - 1]))
		nb_of_tokens++;
	return(nb_of_tokens);
}
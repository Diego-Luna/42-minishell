/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrembla <mtrembla@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:58:06 by mtrembla          #+#    #+#             */
/*   Updated: 2023/01/13 11:25:50 by mtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_splitable(char c)
{
	if (c == ' ' || c == '<' || c == '>' || c == '|')
		return(1);
	return(0);
}

void	ft_minishell_split(char *args, t_tokens *t)
{
	int i = 0;
	int	start = 0;
	char quote;

	while(args[i])
	{
		while (args[i] == '\"' || args[i] == '\'')
			{
				quote = args[i++];
				while(args[i] && args[i++] != quote)
				{}
			}
		if (ft_splitable(args[i]))
		{
			if(args[i - 1] && !ft_splitable(args[i - 1]))
			{
				dlist_add_back(t, ft_substr(args, start, (i - start)));
				start = i;
			}
			if(args[i + 1] && args[i] == args[i + 1])
				i++;
			if (args[i] != ' ')
			dlist_add_back(t, ft_substr(args, start, (i - start + 1)));
			start = i + 1;
		}
		i++;
	}
	if(!ft_splitable(args[i - 1]))
		dlist_add_back(t, ft_substr(args, start, (ft_strlen(args))));
}

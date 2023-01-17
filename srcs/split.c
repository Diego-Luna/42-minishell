/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrembla <mtrembla@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:58:06 by mtrembla          #+#    #+#             */
/*   Updated: 2023/01/16 14:38:27 by mtrembla         ###   ########.fr       */
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
	int i;
	int	start;

	i = 0;
	start = 0;
	while(args[i])
	{
		while (args[i] == '\"' || args[i] == '\'')
				i = ft_quotes(args, i);
		if (ft_splitable(args[i]))
		{
			i = ft_create_token(args, i, start, t);
			start = i + 1;
		}
		if(args[i])
			i++;
	}
	if(!ft_splitable(args[i - 1]))
		dlist_add_back(t, ft_substr(args, start, (ft_strlen(args))));
}

int	ft_quotes(char *args, int i)
{
	char	quote;
	
	quote = args[i++];
	while (args[i])
	{
		while (args[i] != quote)
		i++;
		return(i + 1);
	}
	printf("unclosed quotes\n");
	exit(0);
}

int	ft_create_token(char *args, int i, int start, t_tokens *t)
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
	return (i);
}

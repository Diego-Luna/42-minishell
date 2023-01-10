/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrembla <mtrembla@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:58:06 by mtrembla          #+#    #+#             */
/*   Updated: 2023/01/10 12:53:05 by mtrembla         ###   ########.fr       */
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
				ft_create_token(args, start, i, t);
				start = i;
			}
			if(args[i] == args[i + 1])
				i++;
			if (args[i] != ' ')
			ft_create_token(args, start, (i + 1), t);
			start = i + 1;
		}
		i++;
	}
	if(!ft_splitable(args[i - 1]))
		ft_create_token(args, start, ft_strlen(args), t);
}

void	ft_create_token(char *args, int start, int end, t_tokens *l)
{
	char *token;

	token = malloc(sizeof(char) * (end - start + 1));
	ft_strcpy(token, &args[start], (end - start));
	dlist_add_back(l, token);
}

char	*ft_strcpy(char *dest, char *src, int len)
{
	int i = 0;
	
	while (len--)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
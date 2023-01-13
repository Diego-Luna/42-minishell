/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrembla <mtrembla@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:30:09 by mtrembla          #+#    #+#             */
/*   Updated: 2023/01/11 18:45:37 by mtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_parse(char *line, t_tokens *tokens)
{
	char *args;
	
	args = line;
	tokens = malloc(sizeof(t_tokens));
	ft_minishell_split(args, tokens);
	view(*tokens);
	ft_clean_quotes(tokens->first);
	view(*tokens);
	dlist_free(tokens);
	free(tokens);
}

void	ft_clean_quotes(t_node *n)
{
	char *str = n->content;
	char	quote;
	int	i = 0;

	while(str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			str = ft_trim_char(str, i);
			while(str[i] && str[i] != quote)
				i++;
			if (str[i])
			str = ft_trim_char(str, i);
		}
		else
		i++;
	}
	n->content = str;
}

char	*ft_trim_char(char *str, int ptr)
{
	char *newstr;
	int	i = 0;
	int	j = 0;

	newstr = malloc(sizeof(char *) * ft_strlen(str));
	while (str[i])
	{
		if (i != ptr)
			newstr[j++] = str[i];
		i++;
	}
	newstr[j] = '\0';
	free(str);
	return(newstr);
}

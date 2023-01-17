/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:30:09 by mtrembla          #+#    #+#             */
/*   Updated: 2023/01/17 16:03:22 by mtrembla         ###   ########.fr       */
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
	dlist_free(tokens);
	free(tokens);
}

char *ft_clean_quotes(char *old_str)
{
	char	quote;
	int	i = 0;

	while(old_str[i])
	{
		if (old_str[i] == '\'' || old_str[i] == '\"')
		{
			quote = old_str[i];
			old_str = ft_trim_char(old_str, i);
			while(old_str[i] && old_str[i] != quote)
				i++;
			if (old_str[i])
				old_str = ft_trim_char(old_str, i);
		}
		else
			i++;
	}
	return (old_str);
}

char	*ft_trim_char(char *str, int ptr)
{
	char *newstr;
	int	i = 0;
	int	j = 0;

	// newstr = malloc(sizeof(char *) * ft_strlen(str));
	newstr = ft_calloc(sizeof(char), ft_strlen(str));
	while (str[i])
	{
		if (i != ptr)
		{
			newstr[j++] = str[i];
		}
		i++;
	}
	newstr[j] = '\0';
	ft_free(str);
	return(newstr);
}

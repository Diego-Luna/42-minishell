/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:30:09 by mtrembla          #+#    #+#             */
/*   Updated: 2023/01/25 13:43:06 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_parse(char *line, t_tokens *tokens, t_state *state)
{
	char *args;

	args = line;
	tokens = malloc(sizeof(t_tokens));
	tokens->first =NULL;
	tokens->last =NULL;
	tokens->error = 0;
	ft_repetition_check(args, tokens);
	ft_minishell_split(args, tokens);
	if (!tokens->error)
	view(*tokens);
	ft_minishell(state, line, tokens);
	dlist_free(tokens);
	free(tokens);
}

char *ft_clean_quotes(char *str)
{
	char	quote;
	int		i;

	i = 0;
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
	return (str);
}

char	*ft_trim_char(char *str, int ptr)
{
	char *newstr;
	int	i;
	int	j;

	i = 0;
	j = 0;
	// newstr = malloc(sizeof(char *) * ft_strlen(str));
	newstr = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	while (str[i])
	{
		if (i != ptr)
			newstr[j++] = str[i];
		i++;
	}
	ft_free(str);
	return(newstr);
}

void	ft_repetition_check(char *str, t_tokens *t)
{
	int		count;
	char	c;

	count = 0;
	c = 0;
	while (*str)
	{
		if (*str == '|' || *str == '>' || *str == '<')
			c = *str;
		while (*str++ == c)
			count++;
		if (count > 2)
		{
			printf("ERROR: Too many '%c'\n", c);
			t->error = 1;
			break;
		}
		count = 0;
		str++;
	}
}
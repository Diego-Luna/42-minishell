/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:30:09 by mtrembla          #+#    #+#             */
/*   Updated: 2023/01/17 19:27:12 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_parse(char *line, t_tokens *tokens, t_state *state)
{
	char *args;

	args = line;
	tokens = malloc(sizeof(t_tokens));
	ft_minishell_split(args, tokens);
	view(*tokens);
	ft_minishell(state, line, tokens); // run comands minishell
	dlist_free(tokens);
	free(tokens);
}

// void	ft_clean_quotes(t_node *n)
char *ft_clean_quotes(char *old_str)
{
	// char *str = n->content;
	// char *str;
	char	quote;
	int	i = 0;

	while(old_str[i])
	{
		if (old_str[i] == '\'' || old_str[i] == '\"')
		{
			quote = old_str[i];
			old_str = ft_trim_char(old_str, i);
			while(old_str[i] && old_str[i] != quote)
			{
				i++;
			}
			if (old_str[i])
			{
				old_str = ft_trim_char(old_str, i);
			}
		}
		else
		{
			i++;
		}
	}
	// n->content = str;
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

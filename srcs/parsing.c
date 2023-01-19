/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:30:09 by mtrembla          #+#    #+#             */
/*   Updated: 2023/01/19 13:53:35 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_parse(char *line, t_tokens *tokens, t_state *state)
{
	char *args;

	args = line;
	tokens = malloc(sizeof(t_tokens));
	tokens->first =NULL;
	tokens->last =NULL;
	ft_minishell_split(args, tokens);
	// view(*tokens);
	ft_minishell(state, line, tokens); // run comands minishell
	dlist_free(tokens);
	free(tokens);
}

char *ft_clean_quotes(char *old_str)
{
	char	quote;
	int		i;

	i = 0;
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
	int	i;
	int	j;

	i = 0;
	j = 0;
	newstr = malloc(sizeof(char *) * ft_strlen(str));
	while (str[i])
	{
		if (i != ptr)
			newstr[j++] = str[i];
		i++;
	}
	newstr[j] = '\0';
	ft_free(str);
	return(newstr);
}

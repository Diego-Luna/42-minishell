/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrembla <mtrembla@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:58:06 by mtrembla          #+#    #+#             */
/*   Updated: 2023/01/08 18:31:27 by mtrembla         ###   ########.fr       */
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
	int end = 0;
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
			if(!ft_splitable(args[i - 1]))
			{
				end = i;
				ft_create_token(args, start, end, t);
				start = end;
			}
			if(args[i] == args[i + 1])
				i++;
			end = i + 1;
			if (args[i] != ' ')
			ft_create_token(args, start, end, t);
			start = end;
		}
		i++;
	}
	if(!ft_splitable(args[i - 1]))
	{
		end = ft_strlen(args);
		ft_create_token(args, start, end, t);
	}
}

void	ft_create_token(char *args, int start, int end, t_tokens *l)
{
	char *token;
	token = malloc(sizeof(char) * (end - start + 1));

	ft_strcpy(token, &args[start], (end - start));
	printf("token:%s\n", token);
	if (token)
	free(token);

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
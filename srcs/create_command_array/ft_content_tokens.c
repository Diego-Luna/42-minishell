/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_content_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:53:46 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/02/02 11:54:02 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_ckeck_is_pipe(char *str)
{
	if (ft_strncmp(str, "|\0", 2) == 0 || ft_strncmp(str, "||\0", 2) == 0)
	{
		return (1);
	}
	return (0);
}

int	ft_content_tokens_i(t_node *aff, int number_pipe, int pipe)
{
	int	i;

	i = 0;
	while (aff)
	{
		if (aff->content && ft_ckeck_is_pipe(aff->content) == 1)
			pipe++;
		else if (pipe > number_pipe)
			break ;
		else if (pipe == number_pipe)
			i++;
		aff = aff->next;
	}
	return (i);
}

void	ft_content_tokens_table_else(t_node *aff, int number_pipe, char **table)
{
	int	pipe;
	int	i;

	i = 0;
	pipe = 0;
	while (aff)
	{
		if (aff->content && ft_ckeck_is_pipe(aff->content) == 1)
			pipe++;
		else if (pipe > number_pipe)
			break ;
		else if (pipe == number_pipe)
		{
			table[i] = ft_strdup(aff->content);
			i++;
		}
		aff = aff->next;
	}
}

void	ft_content_tokens_table(t_state *state, t_node *aff, char **table,
		int number_pipe)
{
	int	pipe;
	int	i;

	pipe = 0;
	i = 0;
	if (state->cmd_nmbs == 1)
	{
		while (aff)
		{
			table[i] = ft_strdup(aff->content);
			aff = aff->next;
			i++;
		}
	}
	else
	{
		ft_content_tokens_table_else(aff, number_pipe, table);
	}
}

char	**ft_content_tokens(t_state *state, int number_pipe, t_tokens l)
{
	t_node	*aff;
	char	**table;
	int		i;
	int		pipe;

	i = 0;
	pipe = 0;
	aff = l.first;
	if (state->cmd_nmbs == 1)
	{
		while (aff)
		{
			i++;
			aff = aff->next;
		}
	}
	else
		i = ft_content_tokens_i(aff, number_pipe, pipe);
	table = ft_calloc(sizeof(char *), i + 1);
	aff = l.first;
	ft_content_tokens_table(state, aff, table, number_pipe);
	return (table);
}

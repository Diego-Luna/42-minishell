/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:54:24 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/25 13:34:51 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_save_token_size(t_node *aff, int number_pipe)
{
	int	pipe;
	int	size;

	pipe = 0;
	size = 0;
	while (aff)
	{
		if (ft_strncmp(aff->content, "|\0", 2) == 0)
			pipe++;
		else if (pipe > number_pipe)
			break ;
		else if (pipe == number_pipe)
		{
			size += ft_strlen(aff->content);
			if (aff->next && ft_strncmp(aff->next->content, "|\0", 2) != 0)
			{
				size++;
			}
		}
		aff = aff->next;
	}
	return (size);
}

void	ft_save_token_else(t_node *aff, int number_pipe, int size, char *save)
{
	int	pipe;

	pipe = 0;
	while (aff)
	{
		if (ft_strncmp(aff->content, "|\0", 2) == 0)
		{
			pipe++;
		}
		else if (pipe > number_pipe)
		{
			break ;
		}
		else if (pipe == number_pipe)
		{
			ft_strlcat(save, aff->content, size);
			if (aff->next)
			{
				ft_strlcat(save, " ", 1);
			}
		}
		aff = aff->next;
	}
}

void	ft_save_token_create_save(t_state *state, int number_pipe, char *save,
		int size)
{
	t_node	*aff;

	aff = state->tokens->first;
	if (state->cmd_nmbs == 1)
	{
		while (aff)
		{
			ft_strlcat(save, aff->content, size + 1);
			aff = aff->next;
			if (aff)
				ft_strlcat(save, " ", size + 1);
		}
	}
	else
		ft_save_token_else(aff, number_pipe, size, save);
}

char	*ft_save_token(t_state *state, int number_pipe)
{
	char	*save;
	t_node	*aff;
	int		pipe;
	int		size;

	pipe = 0;
	size = 0;
	aff = state->tokens->first;
	if (state->cmd_nmbs == 1)
	{
		while (aff)
		{
			size += ft_strlen(aff->content) + 1;
			aff = aff->next;
		}
	}
	else
		size = ft_save_token_size(aff, number_pipe);
	size++;
	save = ft_calloc(sizeof(char), size);
	ft_save_token_create_save(state, number_pipe, save, size);
	return (save);
}

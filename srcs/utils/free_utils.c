/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:47:44 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/02/02 12:15:51 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// we make free, and we put at the end a null.
void	*ft_free(void *ptr)
{
	if (ptr)
	{
		free(ptr);
	}
	return (NULL);
}

void	ft_close_fd(void)
{
	int	i;

	i = 3;
	while (i < 200)
	{
		close(i);
		i++;
	}
}

// We free a table
void	**ft_free_table(char **array)
{
	int	i;

	if (!array)
	{
		return (NULL);
	}
	i = -1;
	while (array[++i])
	{
		if (array[i])
		{
			array[i] = ft_free(array[i]);
		}
	}
	array = ft_free(array);
	return (NULL);
}

void	ft_check_exit(t_state *state)
{
	ft_close_fd();
	ft_free_all(state);
	state->stop_pipes = -1;
}

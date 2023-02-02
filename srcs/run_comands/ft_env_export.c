/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 12:12:57 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/02/02 12:32:31 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env_export_check(char *str, t_state *state)
{
	int		i;
	char	**table;

	i = 0;
	if (ft_isalpha(str[0]) == 0 && str[0] != '_')
	{
		table = calloc(sizeof(char *), 2);
		table[0] = ft_strdup(str);
		ft_error_message(M_ERROR_EXPORT, table, state, N_ERROR_EXPORT);
		ft_free_table(table);
		return (1);
	}
	return (0);
}

void	ft_env_export_plus(t_state *state, char *temp, char *str, int size)
{
	char	*temp2;
	char	*join;

	temp2 = ft_find_env(state->g_env, temp);
	join = ft_strjoin(temp2, str);
	ft_free(str);
	str = join;
	size = ft_find_env_index(state->g_env, temp);
	state->g_env[size] = ft_free(state->g_env[size]);
}

int	ft_env_export_procces(t_state *state, char *temp, char *str, int size)
{
	char	*temp2;
	char	*join;

	if (ft_find_env(state->g_env, temp))
	{
		if (ft_strchr_get(str, '=') > 0 && str[ft_strchr_get(str, '=')
				- 1] == '+')
		{
			ft_env_export_plus(state, temp, str, size);
		}
		else
		{
			size = ft_find_env_index(state->g_env, temp);
			state->g_env[size] = ft_free(state->g_env[size]);
		}
	}
	else
	{
		size = ft_size_table(state->g_env);
		state->g_env = ft_crate_env(state->g_env, 2, 1);
	}
	return (size);
}

void	ft_env_export(t_state *state, char *str, int check)
{
	char	*temp;
	int		size;
	int		temp_leng;
	int		i;

	i = 0;
	if (check == 1 && (ft_env_export_check(str, state) == 1 || ft_strchr(str,
				'=') == NULL))
		return ;
	temp_leng = ft_strlen(str);
	temp = ft_calloc(sizeof(char), temp_leng + 1);
	while (str[i] && str[i] != '=')
	{
		temp[i] = str[i];
		i++;
	}
	size = ft_env_export_procces(state, temp, str, size);
	state->g_env[size] = ft_strdup(str);
	ft_free(temp);
}

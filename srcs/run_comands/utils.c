/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:15:00 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/31 15:54:28 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_env_export_check(char *str, t_state *state)
{
	int i;
	char **table;

	i = 0;

	if(ft_isalpha(str[0]) == 0 && str[0] != '_')
	{
		table = calloc(sizeof(char *), 2);
		table[0] = ft_strdup(str);
		ft_error_message(M_ERROR_EXPORT, table, state, N_ERROR_EXPORT);
		ft_free_table(table);
		return (1);
	}
	return (0);
}

void	ft_env_export(t_state *state, char *str, int check)
{
	char	*temp;
	char	*temp2;
	char	*join;
	int		size;
	int		temp_leng;
	int		i;

	i = 0;
	if (check == 1 && (ft_env_export_check(str, state) == 1 || ft_strchr(str, '=') == NULL))
		return ;
	temp_leng = ft_strlen(str);
	temp = ft_calloc(sizeof(char), temp_leng + 1);
	while (str[i] && str[i] != '=')
	{
		temp[i] = str[i];
		i++;
	}
	if (ft_find_env(state->g_env, temp))
	{
		if (ft_strchr_get(str, '=') > 0 && str[ft_strchr_get(str, '=') - 1] == '+')
		{
			temp2 = ft_find_env(state->g_env, temp);
			join = ft_strjoin(temp2, str);
			ft_free(str);
			str = join;
			size = ft_find_env_index(state->g_env, temp);
			state->g_env[size] = ft_free(state->g_env[size]);
		}else
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
	state->g_env[size] = ft_strdup(str);
	ft_free(temp);
}

char	**ft_only_names(char **env)
{
	int		i;
	int		ii;
	int		iii;
	char	**new;
	char	*tem;

	i = 0;
	ii = 0;
	iii = 0;
	new = ft_calloc(sizeof(char *), ft_size_table(env) + 1);
	while (env[i])
	{
		ii = ft_strchr_get(env[i], '=');
		tem = ft_calloc(sizeof(char), ii + 1);
		iii = 0;
		while (iii < ii)
		{
			tem[iii] = env[i][iii];
			iii++;
		}
		new[i] = tem;
		i++;
	}
	return (new);
}

void	ft_env_organized_utils(char **env)
{
	char	*tem;
	int		i;

	i = 0;
	while (env[i])
	{
		if (i >= 1 && ft_strncmp(env[i], env[i - 1], ft_strlen(env[i])) < 0)
		{
			tem = env[i - 1];
			env[i - 1] = env[i];
			env[i] = tem;
			i = 0;
		}
		i++;
	}
}

int ft_env_organized_check(char *str)
{
	int i;
	int leter;

	i = 0;
	leter = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 1)
		{
			leter++;
		}
		i++;
	}
	return (leter);
}

void	ft_env_organized(char **env_original)
{
	int		i;
	char	*tem;
	char	**env;

	i = 0;
	env = ft_only_names(env_original);
	ft_env_organized_utils(env);
	i = 0;
	while (env[i])
	{
		if (ft_env_organized_check(env[i]) != 0)
		{
			tem = ft_strjoin(env[i], "=");
			printf("declare -x %s=\"%s\"\n", env[i], ft_find_env(env_original,
					tem));
			ft_free(tem);
		}
		i++;
	}
	ft_free_table(env);
}

int	ft_add_env(t_state *state, char **past, int check)
{
	int	i;

	if (ft_size_table(past) == 1)
	{
		ft_env_organized(state->g_env);
		return (1);
	}
	i = 1;
	while (i < ft_size_table(past))
	{
		ft_env_export(state, past[i], check);
		i++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_env_varibles_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:51:56 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/01/30 17:52:06 by dluna-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_handle_env_varibles_utils(t_state *state, int *num, int ii, int i)
{
	char	**table;
	char	*new;
	t_cmd	*cmd;

	cmd = &state->cmds[i];
	table = ft_split(cmd->cmd_args[ii], '$');
	while (table[num[4]])
	{
		table[num[4]] = ft_modif(table[num[4]], state->g_env,
				ft_is_delete(state, num, table[num[4]]));
		num[3] += ft_strlen(table[num[4]]);
		num[4]++;
	}
	new = ft_calloc(sizeof(char), num[3] + 1);
	i = 0;
	while (i < num[4])
	{
		ft_str_to_str(new, table[i]);
		ft_free(table[i]);
		i++;
	}
	ft_free(table);
	return (new);
}

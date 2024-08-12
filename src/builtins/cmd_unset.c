/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derey <derey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:09:20 by derey             #+#    #+#             */
/*   Updated: 2024/07/23 08:51:33 by derey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	re_set(t_init *init_shell, int i)
{
	while (init_shell->cpy_env[i + 1] != NULL)
	{
		init_shell->cpy_env[i] = init_shell->cpy_env[i + 1];
		i++;
	}
	init_shell->cpy_env[i] = NULL;
}

void	cmd_unset(char **list, int idx, t_init *init_shell)
{
	int	i;

	if (!list[idx])
		return ;
	while (list[idx])
	{
		i = 0;
		while (init_shell->cpy_env[i] != NULL)
		{
			if (ft_find_str(init_shell->cpy_env[i], list[idx], '=')
				|| ft_str_unset(init_shell->cpy_env[i], list[idx]))
			{
				init_shell->cpy_env[i] = NULL;
				re_set(init_shell, i);
				break ;
			}
			i++;
		}
		idx++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derey <derey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:09:35 by derey             #+#    #+#             */
/*   Updated: 2024/07/16 13:29:23 by derey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_env(t_init *init_shell, int fd)
{
	int	i;

	i = 0;
	while (init_shell->cpy_env[i] != NULL)
	{
		if (ft_strnstr(init_shell->cpy_env[i], "=",
				ft_strlen(init_shell->cpy_env[i])))
		{
			ft_putstr_fd(init_shell->cpy_env[i], fd);
			ft_putchar_fd('\n', fd);
		}
		i++;
	}
}

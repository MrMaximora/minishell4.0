/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derey <derey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:14:25 by derey             #+#    #+#             */
/*   Updated: 2024/08/01 09:09:10 by derey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
}

void	error_expand(t_init *init_shell)
{
	ft_putstr_fd(" command not found\n", 2);
	init_shell->exit_code = 127;
}

int	error_cd(t_input *line, int i, t_init *init_shell)
{
	if (i >= 1)
	{
		if (line->all_tokens[0] != NULL && line->all_tokens[1] == NULL)
			return (0);
		if (!line->all_tokens[i] || ft_isdigit(line->all_tokens[i][0]) != 0)
		{
			ft_putstr_fd(" No such file or directory\n", 2);
			init_shell->exit_code = 1;
			return (1);
		}
		if (line->all_tokens[i + 1] != NULL)
		{
			ft_putstr_fd(" too many arguments\n", 2);
			init_shell->exit_code = 1;
			return (1);
		}
	}
	return (0);
}

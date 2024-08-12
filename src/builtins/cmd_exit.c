/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derey <derey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:09:49 by derey             #+#    #+#             */
/*   Updated: 2024/08/09 14:47:50 by derey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	verif_aplha(t_input *line, int i)
{
	int	x;

	x = 0;
	while (line->all_tokens[i][x] != '\0')
	{
		if (line->all_tokens[i][0] == ' ')
		{
			while (line->all_tokens[i][x] == ' '
				&& line->all_tokens[i][x] != '\0')
				x++;
		}
		if (ft_isdigit(line->all_tokens[i][x]) == 0)
		{
			if ((line->all_tokens[i][x] == '+' || line->all_tokens[i][x] == '-')
				&& ft_isdigit(line->all_tokens[i][x + 1]) == 0)
				return (1);
			else if ((line->all_tokens[i][x] != '+'
				&& line->all_tokens[i][x] != '-')
				&& ft_isdigit(line->all_tokens[i][x]) == 0)
				return (1);
		}
		x++;
	}
	return (0);
}

int	verif_len_exit(t_input *line, int i)
{
	if (ft_strlen(line->all_tokens[i]) == 19)
	{
		if (ft_strcmp("9223372036854775807", line->all_tokens[i]) == 1)
			return (2);
	}
	if (ft_strlen(line->all_tokens[i]) == 20)
	{
		if (ft_strcmp("-9223372036854775808", line->all_tokens[i]) == 1)
			return (2);
	}
	while (line->all_tokens[i] != NULL)
	{
		if (line->all_tokens[i][0] == '|')
			return (0);
		i++;
	}
	return (1);
}

void	cmd_exit(t_input *line, int i, t_init *init_shell)
{
	init_shell->on = 0;
	if (!line->all_tokens[i])
		;
	else if (line->all_tokens[i][0] == '<' || line->all_tokens[i][0] == '>')
		;
	else if ((verif_aplha(line, i) == 1 || verif_len_exit(line, i) == 2)
		&& verif_len_exit(line, i) != 0)
	{
		init_shell->exit_code = 2;
		ft_putstr_fd(" numeric argument required\n", 2);
	}
	else if (line->all_tokens[i + 1] != NULL && verif_len_exit(line, i) != 0)
	{
		init_shell->exit_code = 1;
		init_shell->on = 1;
		ft_putstr_fd(" too many arguments\n", 2);
	}
	else
		init_shell->exit_code = ft_atoi(line->all_tokens[i]);
	ft_printf("exit\n");
}

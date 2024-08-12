/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derey <derey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:03:50 by derey             #+#    #+#             */
/*   Updated: 2024/07/23 08:55:29 by derey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*search_alpha(char *result, char **list)
{
	int	i;

	i = 0;
	while (list[i] != NULL)
	{
		if (ft_strcmp(list[i], result) == 1 && ft_strcmp(list[i], "0") != 2)
		{
			free(result);
			result = ft_strdup(list[i]);
		}
		i++;
	}
	return (result);
}

void	loop_alpha(int y, char **list)
{
	int		i;
	char	*result;

	i = 0;
	while (y >= 0)
	{
		i = 0;
		while (ft_strcmp(list[i], "0") == 2)
			i++;
		result = ft_strdup(list[i]);
		result = search_alpha(result, list);
		print_ex(result);
		i = 0;
		while (list[i] != NULL)
		{
			if (ft_strcmp(list[i], result) == 2)
			{
				free(list[i]);
				list[i] = ft_strdup("0");
			}
			i++;
		}
		free(result);
		y--;
	}
}

char	**list_alpha(int i, int a, t_init *init_shell)
{
	char	**list;
	int		y;

	y = 0;
	list = ft_calloc(sizeof(char *), (i + 1));
	y = 0;
	i = 0;
	while (init_shell->cpy_env[i] != NULL)
	{
		if (ft_strstr(init_shell->cpy_env[i], 65 + a, 0) == 1)
		{
			list[y] = ft_strdup(init_shell->cpy_env[i]);
			y++;
		}
		i++;
	}
	list[y] = NULL;
	return (list);
}

int	cmp_alpha(int a, t_init *init_shell)
{
	int	i;
	int	cmp;

	i = 0;
	cmp = 0;
	while (init_shell->cpy_env[i] != NULL)
	{
		if (ft_strstr(init_shell->cpy_env[i], 65 + a, 0) == 1)
		{
			cmp++;
		}
		i++;
	}
	return (cmp);
}

void	print_export(t_init *init_shell)
{
	int		a;
	int		i;
	char	**list;
	int		y;

	a = 0;
	while (a <= 60)
	{
		i = cmp_alpha(a, init_shell);
		if (i > 1)
		{
			list = list_alpha(i, a, init_shell);
			y = ft_strlen_list(list);
			loop_alpha(y - 1, list);
			i = 0;
			while (list[i] != NULL)
				free(list[i++]);
			free(list);
		}
		else if (i == 1)
			print_solo(a, init_shell);
		a++;
	}
}

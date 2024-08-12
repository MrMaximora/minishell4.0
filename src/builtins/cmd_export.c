/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derey <derey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:09:08 by derey             #+#    #+#             */
/*   Updated: 2024/08/07 16:36:39 by derey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	realloc_env(t_init *init_shell, char *str, int i)
{
	char	**tmp;

	tmp = ft_calloc(sizeof(char *), (i + 2));
	i = 0;
	while (init_shell->cpy_env && init_shell->cpy_env[i])
	{
		tmp[i] = ft_strdup(init_shell->cpy_env[i]);
		free(init_shell->cpy_env[i]);
		i++;
	}
	free(init_shell->cpy_env);
	tmp[i] = NULL;
	i = 0;
	while (tmp[i])
		i++;
	init_shell->cpy_env = ft_calloc(sizeof(char *), (i + 2));
	i = 0;
	while (tmp[i])
	{
		init_shell->cpy_env[i] = ft_strdup(tmp[i]);
		free(tmp[i++]);
	}
	init_shell->cpy_env[i] = ft_strdup(str);
	init_shell->cpy_env[i + 1] = NULL;
	free(tmp);
}

void	modif_env(t_init *init_shell, char *str)
{
	int		i;
	int		x;
	char	*tmp;

	i = 0;
	x = 0;
	tmp = ft_calloc(sizeof(char *), ft_strlen(str));
	while (str[x] != '\0' && str[x] != '=')
	{
		tmp[i] = str[i];
		x++;
		i++;
	}
	i = 0;
	while (init_shell->cpy_env[i] != NULL)
	{
		if (ft_find_export(init_shell->cpy_env[i], tmp, '='))
		{
			free(init_shell->cpy_env[i]);
			init_shell->cpy_env[i] = ft_strdup(str);
			break ;
		}
		i++;
	}
	free(tmp);
}

int	verif_export(char *str, t_init *init_shell)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_calloc(sizeof(char *), ft_strlen(str));
	while (str[i] && str[i] != '=')
	{
		tmp[i] = str[i];
		i++;
	}
	i = 0;
	while (init_shell->cpy_env[i])
	{
		if (ft_find_export(init_shell->cpy_env[i], tmp, '='))
		{
			free(tmp);
			return (1);
		}
		i++;
	}
	free(tmp);
	return (2);
}

static void	export_loop(char **list, int idx, t_init *init_shell)
{
	int	i;

	i = 0;
	while (init_shell->cpy_env[i] != NULL)
		i++;
	if (i == 0)
	{
		init_shell->cpy_env = ft_calloc(sizeof(char *), 2);
		init_shell->cpy_env[0] = ft_strdup(list[idx]);
		init_shell->cpy_env[1] = NULL;
	}
	else if (verif_export(list[idx], init_shell) == 1)
		modif_env(init_shell, list[idx]);
	else
		realloc_env(init_shell, list[idx], i);
}

void	cmd_export(char **list, int idx, t_init *init_shell)
{
	if (list[1] == NULL || list[1][0] == '\0' || list[1][0] == '|')
		print_export(init_shell);
	else
	{
		while (list[idx] != NULL)
		{
			if (list[idx][0] == '|')
			{
				init_shell->exit_code = 1;
				break ;
			}
			if (list[idx][0] != '|' && verif_str(list[idx]) == 1)
			{
				init_shell->exit_code = 1;
				ft_putstr_fd(" not a valid identifier\n", 2);
				idx++;
				continue ;
			}
			export_loop(list, idx, init_shell);
			idx++;
		}
	}
}

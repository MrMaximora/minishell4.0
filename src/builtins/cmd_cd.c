/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derey <derey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:06:36 by derey             #+#    #+#             */
/*   Updated: 2024/08/09 13:11:25 by derey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*cd_homes(t_init *init_shell)
{
	int		i;
	int		x;
	int		y;
	char	*result;

	x = 5;
	i = 0;
	while (init_shell->cpy_env[i] != NULL)
	{
		if (ft_strnstr(init_shell->cpy_env[i], "HOME=",
				ft_strlen(init_shell->cpy_env[i])))
		{
			y = ft_strlen(init_shell->cpy_env[i]);
			result = ft_calloc(y - 4, sizeof(char));
			y = 0;
			while (init_shell->cpy_env[i][x] != '\0')
				result[y++] = init_shell->cpy_env[i][x++];
			return (result);
		}
		i++;
	}
	ft_putstr_fd(" HOME not set\n", 2);
	init_shell->exit_code = 1;
	return (NULL);
}

static char	*cd_back(char *str)
{
	int		i;
	int		x;
	char	*result;

	x = 0;
	i = ft_strlen(str);
	result = ft_calloc(i, sizeof(char *));
	while (str[i] != '/')
	{
		i--;
	}
	while (x <= i)
	{
		result[x] = str[x];
		x++;
	}
	result[x] = '\0';
	return (result);
}

void	change_env(char *oldpwd, char *pwd, t_init *init_shell)
{
	int	i;

	i = 0;
	while (init_shell->cpy_env[i] != NULL)
		i++;
	if (!oldpwd)
		oldpwd = pwd;
	oldpwd = ft_strjoin("OLDPWD=", oldpwd);
	pwd = ft_strjoin("PWD=", pwd);
	if (verif_export(oldpwd, init_shell) == 1)
		modif_env(init_shell, oldpwd);
	else
		realloc_env(init_shell, oldpwd, i);
	free(oldpwd);
	if (verif_export(pwd, init_shell) == 1)
		modif_env(init_shell, pwd);
	else
		realloc_env(init_shell, pwd, i);
	free(pwd);
}

void	cd_end(char	*oldpwd, char *result, t_init *init_shell)
{
	if (access(result, F_OK) == -1)
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		init_shell->exit_code = 1;
		return ;
	}
	if (access(result, F_OK | R_OK) != 0)
	{
		ft_putstr_fd(" Permission denied\n", 2);
		init_shell->exit_code = 1;
		return ;
	}
	chdir(result);
	free(init_shell->pathearly);
	init_shell->pathearly = ft_strdup(result);
	path_early(init_shell);
	change_env(oldpwd, result, init_shell);
	free(result);
}

void	cmd_cd(t_input *line, int i, t_init *init_shell)
{
	char	c[PATH_MAX];
	char	*result;
	char	*join;
	char	*oldpwd;

	if (getcwd(c, sizeof(c)) != NULL)
		oldpwd = c;
	if (error_cd(line, 1, init_shell) == 1)
		return ;
	else if (!line->all_tokens[i])
		result = cd_homes(init_shell);
	else if (ft_strnstr(line->all_tokens[i], "..", 2))
		result = cd_back(c);
	else if (access(line->all_tokens[i], F_OK | R_OK) == 0)
		result = ft_strdup(line->all_tokens[i]);
	else
	{
		join = ft_strjoin(c, "/");
		result = ft_strjoin(join, line->all_tokens[i]);
		free(join);
	}
	if (result == NULL)
		return ;
	cd_end(oldpwd, result, init_shell);
}

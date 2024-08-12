/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derey <derey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:06:52 by derey             #+#    #+#             */
/*   Updated: 2024/08/09 16:43:39 by derey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_ex(char *result)
{
	int	x;

	x = 0;
	ft_putstr_fd("declare -x ", 1);
	x = print_var(result, 1, x, '=');
	if (x != -1)
	{
		ft_putstr_fd("\"", 1);
		x = print_var(result, 1, x + 1, '\0');
		ft_putstr_fd("\"", 1);
	}
	ft_putchar_fd('\n', 1);
}

void	print_solo(int a, t_init *init_shell)
{
	int	i;

	i = 0;
	while (init_shell->cpy_env[i] != NULL)
	{
		if (ft_strstr(init_shell->cpy_env[i], 65 + a, 0) == 1)
			print_ex(init_shell->cpy_env[i]);
		i++;
	}
}

int	print_var(char *s, int fd, int i, char c)
{
	if (s != NULL)
	{
		while (s[i] != c && s[i] != '\0' )
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
	if (s[i] == '=')
		write(fd, "=", 1);
	if (s[i] == '\0')
		return (-1);
	return (i);
}

char	*ft_find_export(const char *big, const char *little, char find)
{
	size_t	i;
	int		x;
	int		a;

	i = 0;
	if (!*little || little[i] == '\0' || big == NULL)
		return ((char *)big);
	while (big[i])
	{
		x = 0;
		a = i;
		while (big[i] == little[x] && big[i])
		{
			i++;
			x++;
		}
		if (little[0] == big[0] && little[x] == '\0'
			&& (big[i] == find || big[i] == '\0'))
				return ((char *)&big[i - x]);
		i = a;
		i++;
	}
	if (little[0] == big[0] && little[x] == '\0'
		&& (big[i] == find || big[i] == '\0'))
		return ((char *)&big[i - x]);
	return (NULL);
}

int	verif_str(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '=')
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (ft_isdigit(str[i]) != 0)
			return (1);
		else if ((str[i] < 48 || str[i] > 122))
			return (1);
		else if ((str[i] > 57 && str[i] < 65))
			return (1);
		else if ((str[i] > 90 && str[i] < 97))
			return (1);
		i++;
	}
	return (0);
}

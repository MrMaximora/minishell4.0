/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derey <derey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 09:26:04 by derey             #+#    #+#             */
/*   Updated: 2024/08/09 14:28:15 by derey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strstr(const char *big, const char little, int i)
{
	if (big[i] == little)
		return (1);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *) s1;
	b = (unsigned char *) s2;
	i = 0;
	while ((a[i] || b[i]))
	{
		if (a[i] < b[i])
			return (1);
		if (a[i] > b[i])
			return (0);
		i++;
	}
	return (2);
}

char	*ft_str_unset(const char *big, const char *little)
{
	size_t	i;
	int		x;
	int		a;

	i = 0;
	if (!*little || little[i] == '\0' || big == NULL)
		return ((char *)big);
	while (big[i] != '\0')
	{
		x = 0;
		a = i;
		while (big[i] == little[x] && big[i])
		{
			i++;
			x++;
		}
		if (little[x] == '\0' && big[i] == '\0')
			return ((char *)&big[i - x]);
		i = a;
		i++;
	}
	return (NULL);
}

int	find_homes(t_init *init_shell)
{
	int	i;

	i = 0;
	while (init_shell->cpy_env[i] != NULL)
	{
		if (ft_strnstr(init_shell->cpy_env[i], "HOME=",
				ft_strlen(init_shell->cpy_env[i])))
		{
			i = ft_strlen(init_shell->cpy_env[i]) - 5;
			break ;
		}
		i++;
	}
	if (init_shell->cpy_env[i] == NULL)
		return (0);
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derey <derey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:14:46 by derey             #+#    #+#             */
/*   Updated: 2024/07/22 11:15:58 by derey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_joinlen(char const *s1, char const *s2, int a)
{
	size_t	i;
	size_t	j;
	char	*result;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	result = ft_calloc(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + a + 1);
	if (!result)
		return (NULL);
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}

char	*ft_expcpy(char *str, char c, int z)
{
	char	*result;
	int		i;
	int		a;

	i = 0;
	a = 0;
	result = ft_calloc(z, sizeof(char));
	while (str[i] != c && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (result);
	i++;
	while (str[i] != '\0' && a < z)
	{
		result[a] = str[i];
		a++;
		i++;
	}
	return (result);
}

char	*print_expend(const char *s, int c)
{
	int		i;

	i = 0;
	c = (char) c;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			i++;
			return ((char *)&s[i]);
		}
		i++;
	}
	if (!c)
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_find_str(const char *big, const char *little, char find)
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
		if (little[0] == big[0] && little[x] == '\0' && big[i] == find)
			return ((char *)&big[i - x]);
		i = a;
		i++;
	}
	return (NULL);
}

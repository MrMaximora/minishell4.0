/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derey <derey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:59:12 by derey             #+#    #+#             */
/*   Updated: 2024/07/23 08:55:30 by derey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strexit(char *str)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			while (str[i] == '?' && str[i] != '\0')
				i++;
			break ;
		}
		i++;
	}
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			while (str[i] == ' ' && str[i] != '\0')
				i++;
		i++;
		a++;
	}
	return (a);
}

int	ft_strlenback(char *str)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			while (str[i] == ' ' && str[i] != '\0')
				i++;
			break ;
		}
		i++;
	}
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			while (str[i] == ' ' && str[i] != '\0')
				i++;
		i++;
		a++;
	}
	return (a);
}

int	ft_strlenlen(char *str, int x)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			while (str[i] != '\0' && str[i] != ' ')
				i++;
		}
		else if (str[i] == '"')
			i++;
		else if (str[i] == '\'')
			i++;
		else
		{
			i++;
			a++;
		}
	}
	a = a + x;
	return (a);
}

int	ft_strlen_exp(char *str, char c)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (str[i] != c && str[i] != '\0')
	{
		i++;
	}
	if (str[i] != '\0' && str[i + 1] != '\0')
	{
		i++;
		while (str[i] != '\0')
		{
			i++;
			a++;
		}
	}
	return (a);
}

int	ft_strlen_list(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != NULL)
		i++;
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split_p2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derey <derey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:15:40 by derey             #+#    #+#             */
/*   Updated: 2024/07/23 09:17:07 by derey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_len(char const *str, size_t	i, size_t n)
{
	int	a;

	a = 0;
	while (i < n && str[i] != '\0')
	{
		a++;
		i++;
	}
	return (a);
}

char	*ft_substr_exp(char const *s, unsigned int start, size_t len)
{
	size_t	x;
	char	*result;

	x = 0;
	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	result = ft_calloc(ft_len(s, start, len) + 1, sizeof(char));
	if (!result)
		return (NULL);
	while (start < len && s[start] != '\0')
	{
		result[x] = s[start];
		x++;
		start++;
	}
	result[x] = '\0';
	return (result);
}

void	space_verif(t_exp *expa)
{
	if (expa->dquot != -1 && expa->space < expa->dquot)
		expa->q = 1;
	else if (expa->squot != -1 && expa->space < expa->squot)
		expa->q = 1;
	else if (expa->dquot == -1 && expa->squot == -1)
		expa->q = 1;
}

void	dquot_verif(t_exp *expa)
{
	if (expa->space != -1 && expa->dquot < expa->space)
		expa->q = 2;
	else if (expa->squot != -1 && expa->dquot < expa->squot)
		expa->q = 2;
	else if (expa->space == -1 && expa->squot == -1)
		expa->q = 2;
}

void	squot_verif(t_exp *expa)
{
	if (expa->space != -1 && expa->squot < expa->space)
		expa->q = 3;
	else if (expa->dquot != -1 && expa->squot < expa->dquot)
		expa->q = 3;
	else if (expa->space == -1 && expa->dquot == -1)
		expa->q = 3;
}

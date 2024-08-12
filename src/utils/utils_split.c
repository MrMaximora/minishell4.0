/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derey <derey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:40:07 by derey             #+#    #+#             */
/*   Updated: 2024/08/09 14:24:16 by derey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	ft_countword(char const *s, char c)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			len++;
		if (*s == '|')
			len++;
		while (*s != c && *s)
			s++;
	}
	return (len);
}

int ft_loopidxexp(char const *s, t_exp *expa, int i)
{
	expa->squot = 0;
	expa->dquot = 0;
	while (s[i] != ' ' && s[i] != '\0')
	{
		while (s[i] != '\0')
		{
			if (s[i] == '\'')
				expa->squot++;
			if (s[i] == '"')
				expa->dquot++;
			i++;
			if (expa->squot % 2 == 0 && expa->dquot % 2 == 0)
				break ;
			
		}
	}
	expa->dquot = -1;
	expa->squot = -1;
	return (i);
}

void	ft_idxexp(char const *s, t_exp *expa, int i)
{
	while (s[i] != '\0' && s[i] != '\'' && s[i] != '"' && s[i] != ' ' && s[i] != '|')
		i++;
	if (s[i] == '\'' && (s[i - 1] == ' ' || s[i - 1] == '=' ))
	{
		
		expa->squot = ft_loopidxexp(s, expa, i) - 1;
		expa->dquot = -1;
	}
	else if (s[i] == '"' && (s[i - 1] == ' ' || s[i - 1] == '=' ))
	{
		expa->dquot = ft_loopidxexp(s, expa, i) - 1;
		expa->squot = -1;
	}
	else if (s[i] == ' ' || s[i] == '\0')
		expa->space = i;
	else if (s[i] == '|')
		expa->pipe = i;
	else
	{
		expa->space = ft_loopidxexp(s, expa, i);
		expa->squot = -1;
		expa->dquot = -1;
	}
}

int	sub_slit(char const *s, t_exp *expa, t_input *line, int i)
{
	if (expa->q == 1)
	{
		expa->len = expa->space;
		line->all_tokens[expa->x] = ft_substr_exp(s, i, expa->len);
		expa->space = -1;
	}
	else if (expa->q == 2)
	{
		expa->len = expa->dquot + 1;
		line->all_tokens[expa->x] = ft_substr_exp(s, i, expa->len);
		expa->dquot = -1;
	}
	else if (expa->q == 3)
	{
		expa->len = expa->squot + 1;
		line->all_tokens[expa->x] = ft_substr_exp(s, i, expa->len);
		expa->squot = -1;
	}
	else if (expa->q == 4)
	{
		if (expa->pipe == 0 || s[expa->pipe - 1] == ' ')
			expa->len = expa->pipe + 1;
		else
		{
			expa->len = expa->pipe;
			line->all_tokens[expa->x] = ft_substr_exp(s, i, expa->len);
			i = expa->len;
			expa->x++;
			expa->len++;
		}
		line->all_tokens[expa->x] = ft_substr_exp(s, i, expa->len);
		expa->pipe = -1;
	}
	else if (!ft_strchr(s, ' '))
	{
		expa->len = ft_strlen(s);
		line->all_tokens[expa->x] = ft_substr_exp(s, i, expa->len);
	}
	expa->x++;
	return (expa->len);
}

void	ft_loop(char const *s, t_exp *expa, t_input *line)
{
	int	i;

	i = 0;
	expa->squot = -1;
	expa->dquot = -1;
	expa->space = -1;
	while (s[i] != '\0')
	{
		while (s[i] == ' ' ||  s[i] == '\t' || s[i] == '\b' || s[i] == '\n')
			i++;
		ft_idxexp(s, expa, i);
		if (expa->space != -1)
			space_verif(expa);
		else if (expa->dquot != -1)
			dquot_verif(expa);
		else if (expa->squot != -1)
			squot_verif(expa);
		else if (expa->pipe != -1)
			expa->q = 4;
		if (s[i])
			i = sub_slit(s, expa, line, i);
	}
}

void	ft_split_expand(char const *s, t_exp *expa, t_input *line)
{
	if (s == NULL)
		return ;
	line->all_tokens = ft_calloc((ft_countword(s, ' ') + 2), sizeof(char *));
	if (!line->all_tokens)
		return ;
	ft_loop(s, expa, line);
	line->all_tokens[expa->x] = NULL;
}

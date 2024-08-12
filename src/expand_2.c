/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derey <derey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:17:45 by derey             #+#    #+#             */
/*   Updated: 2024/08/08 09:39:03 by derey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	quot_exp(t_exp *expa, t_input *line)
{
	if (line->all_tokens[expa->idx_tab][expa->idx] == '"' && expa->squot == 0)
	{
		if (expa->dquot == 0)
			expa->dquot = 1;
		else
			expa->dquot = 0;
	}
	else if (line->all_tokens[expa->idx_tab][expa->idx] == '\''
		&& expa->dquot == 0)
	{
		if (expa->squot == 0)
			expa->squot = 1;
		else
			expa->squot = 0;
	}
}

int	end_word(char c)
{
	int	i;

	if ((c < 48 || c > 122) && c != '$' && c != '?' && c != '\0')
		i = 1;
	else if ((c > 57 && c < 65) && c != '$' && c != '?' && c != '\0')
		i = 1;
	else if ((c > 90 && c < 97) && c != '$' && c != '?' && c != '\0')
		i = 1;
	else
		i = 0;
	return (i);
}

void	text_exp(t_exp *expa, t_init *init_shell, t_input *line, int a)
{
	char	*tmp;
	int		st;

	tmp = NULL;
	st = 0;
	if (a == 0 && line->all_tokens[expa->idx_tab][expa->idx + 1] == '?')
	{
		expa->exp = ft_itoa(init_shell->exit_code);
		st = ft_strexit(line->all_tokens[expa->idx_tab]);
	}
	else
		expa->exp = ft_expcpy(init_shell->cpy_env[a],
				'=', ft_strlen_exp(init_shell->cpy_env[a], '=') + 1);
	tmp = ft_joinlen(expa->end_str, expa->exp,
			ft_strlenback(line->all_tokens[expa->idx_tab]) + st);
	if (tmp == NULL)
		return ;
	free(expa->end_str);
	expa->end_str = tmp;
	if (a == 0 && line->all_tokens[expa->idx_tab][expa->idx + 1] == '?')
	{
		expa->idx = expa->idx + 2;
		expa->len = expa->len + ft_strlen(expa->exp);
	}
	free(expa->exp);
}

void	word_expand(t_exp *expa, t_input *line)
{
	int	i;
	int	a;

	a = 0;
	i = expa->idx;
	while (line->all_tokens[expa->idx_tab][i] != '\0'
		&& end_word(line->all_tokens[expa->idx_tab][i]) == 0)
	{
		i++;
		a++;
	}
	expa->word_env = ft_calloc(a + 2, sizeof(char));
	if (expa->word_env == NULL)
		return ;
	expa->idx++;
	i = 0;
	while (line->all_tokens[expa->idx_tab][expa->idx] != '\0'
		&& end_word(line->all_tokens[expa->idx_tab][expa->idx]) == 0
		&& line->all_tokens[expa->idx_tab][expa->idx] != '$')
	{
		expa->word_env[i] = line->all_tokens[expa->idx_tab][expa->idx];
		i++;
		expa->idx++;
	}
}

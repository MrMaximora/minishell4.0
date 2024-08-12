/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derey <derey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:27:04 by derey             #+#    #+#             */
/*   Updated: 2024/08/07 16:00:52 by derey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	write_noexp(t_exp *expa, t_input *line)
{
	if ((line->all_tokens[expa->idx_tab][expa->idx] != '"'
		&& line->all_tokens[expa->idx_tab][expa->idx] != '\'') && line->all_tokens[expa->idx_tab][expa->idx] != '$')
		expa->end_str[expa->len++] = line->all_tokens[expa->idx_tab][expa->idx];
	else if (expa->dquot != 0
		&& line->all_tokens[expa->idx_tab][expa->idx] != '"')
		expa->end_str[expa->len++] = line->all_tokens[expa->idx_tab][expa->idx];
	else if (expa->squot != 0
		&& line->all_tokens[expa->idx_tab][expa->idx] != '\'')
		expa->end_str[expa->len++] = line->all_tokens[expa->idx_tab][expa->idx];
	else if (line->all_tokens[expa->idx_tab][expa->idx] == '$' && line->all_tokens[expa->idx_tab][expa->idx + 1] == '\0')
		expa->end_str[expa->len++] = line->all_tokens[expa->idx_tab][expa->idx];
	expa->idx++;
}

void	loop_exp(t_exp *expa, t_init *init_shell, t_input *line, int a)
{
	int	i;

	i = 0;
	if (init_shell->cpy_env[a] == NULL || expa->word_env == NULL )
		return ;
	while (init_shell->cpy_env[a][i] == expa->word_env[i]
		&& expa->word_env[i] != '\0')
	{
		if (init_shell->cpy_env[a][i + 1] == '='
			&& (expa->word_env[i + 1] == '\0' || expa->word_env[i + 1] == '$'))
		{
			text_exp(expa, init_shell, line, a);
			expa->len = expa->len
				+ ft_strlen_exp(init_shell->cpy_env[a], '=');
			break ;
		}
		i++;
	}
}

void	write_exp(t_exp *expa, t_input *line, t_init *init_shell)
{
	int		a;

	if (line->all_tokens[expa->idx_tab][expa->idx] == '$'
		&& line->all_tokens[expa->idx_tab][expa->idx + 1] == '\0')
		return ;
	if (line->all_tokens[expa->idx_tab][expa->idx] == '$'
		&& end_word(line->all_tokens[expa->idx_tab][expa->idx + 1])
			== 0 && expa->squot == 0)
	{
		while (line->all_tokens[expa->idx_tab][expa->idx] != '\0' && line->all_tokens[expa->idx_tab][expa->idx] == '$')
		{
			if (line->all_tokens[expa->idx_tab][expa->idx] == '$'
				&& line->all_tokens[expa->idx_tab][expa->idx + 1] == '\0')
				return ;
			if (line->all_tokens[expa->idx_tab][expa->idx] == '$'
			&& line->all_tokens[expa->idx_tab][expa->idx + 1] == '?')
			text_exp(expa, init_shell, line, 0);
			else
				word_expand(expa, line);
			a = 0;
			while (init_shell->cpy_env[a] != NULL)
				loop_exp(expa, init_shell, line, a++);
			free(expa->word_env);
			if (line->all_tokens[expa->idx_tab][expa->idx] == '\'' || line->all_tokens[expa->idx_tab][expa->idx] == '"')
				quot_exp(expa, line);
		}
	}
	else if (line->all_tokens[expa->idx_tab][expa->idx] == '$'
		&& end_word(line->all_tokens[expa->idx_tab][expa->idx + 1]) != 0
		&& line->all_tokens[expa->idx_tab][expa->idx] == '\'')
		error_expand(init_shell);
}

static void	expand_loop(t_input *line, t_init *init_shell, t_exp *expa)
{
	int	i;

	init_exp(expa, line);
	expa->dquot = 0;
	expa->squot = 0;
	i = ft_strlen(line->all_tokens[expa->idx_tab]);
	expa->end_str = ft_calloc(i + 2, sizeof(char));
	expa->idx = 0;
	while (line->all_tokens[expa->idx_tab][expa->idx] != '\0')
	{
		quot_exp(expa, line);
		write_exp(expa, line, init_shell);
		if (line->all_tokens[expa->idx_tab][expa->idx] == '\0')
			break ;
		write_noexp(expa, line);
	}
	free(line->all_tokens[expa->idx_tab]);
	line->all_tokens[expa->idx_tab] = ft_strdup(expa->end_str);
	expa->idx_tab++;
	free(expa->end_str);
	expa->end_str = 0;
}

void	ft_expand(t_input *line, t_init *init_shell)
{
	t_exp	*expa;

	expa = ft_calloc(1, sizeof(t_exp));
	expa->idx_tab = 0;
	init_exp(expa, line);
	ft_split_expand(line->input, expa, line);
	init_exp(expa, line);
	if (expa->dquot > 0 || expa->squot > 0 || expa->expan > 0)
	{
		expa->dquot = 0;
		expa->squot = 0;
		while (line->all_tokens[expa->idx_tab])
			expand_loop(line, init_shell, expa);
	}
	else
		free(expa->tmp_exp);
	free(expa);
}

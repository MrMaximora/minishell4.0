/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derey <derey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:51:03 by derey             #+#    #+#             */
/*   Updated: 2024/08/05 09:40:17 by derey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token_type	ft_lexer(char *current_token)
{
	static t_token	list_token[] = {
	{"<", TOKEN_REDIRECT_INPUT},
	{">", TOKEN_REDIRECT_OUTPUT}, {"<<", TOKEN_DELIMITER},
	{">>", TOKEN_APPEND}, {"|", TOKEN_PIPE},
	{"\\", TOKEN_BACKSLASH}, {";", TOKEN_SEMICOLON},
	{"cd", TOKEN_BUILTIN}, {"$", TOKEN_EXPAND},
	{"echo", TOKEN_BUILTIN}, {"env", TOKEN_BUILTIN},
	{"exit", TOKEN_BUILTIN}, {"exit", TOKEN_BUILTIN},
	{"export", TOKEN_BUILTIN}, {"pwd", TOKEN_BUILTIN},
	{"unset", TOKEN_BUILTIN}, {NULL, TOKEN_ARGS}
	};
	static size_t	index;

	index = 0;
	while (list_token[index].symbol != NULL)
	{
		if (strcmp(current_token, list_token[index].symbol) == 0)
			return (list_token[index].type);
		index++;
	}
	return (TOKEN_ARGS);
}

t_lexer_tab	*create_lexer_tab(t_lexer_tab *tab_lexer, t_input *line, int i)
{
	append_node(&tab_lexer, line, i);
	return (tab_lexer);
}

void	stack_add_back(t_lexer_tab **tab_lexer, t_lexer_tab *new)
{
	if (!new)
		return ;
	if (!*tab_lexer)
	{
		*tab_lexer = new;
		return ;
	}
	(get_last_node(*tab_lexer)->next = new);
}

t_lexer_tab	*ft_new_node(int i, t_input *line)
{
	t_lexer_tab	*new;

	new = malloc(sizeof (t_lexer_tab));
	if (!new)
		return (NULL);
	new->index = i;
	new->len = ft_strlen(line->all_tokens[i]);
	new->arg = line->all_tokens[i];
	new->type = ft_lexer(line->all_tokens[i]);
	new->infile = 0;
	new->outfile = 0;
	new->next = NULL;
	return (new);
}

t_lexer_tab	*get_last_node(t_lexer_tab *node)
{
	if (!node)
		return (NULL);
	if (!node->next)
		return (node);
	while (node->next)
		node = node->next;
	return (node);
}

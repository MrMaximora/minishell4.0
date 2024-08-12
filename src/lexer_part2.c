/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_part2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derey <derey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 09:33:37 by derey             #+#    #+#             */
/*   Updated: 2024/07/23 09:35:07 by derey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	append_node(t_lexer_tab **tab_lexer, t_input *line, int i)
{
	if (!*tab_lexer)
		*tab_lexer = ft_new_node(i, line);
	else
		stack_add_back(tab_lexer, ft_new_node(i, line));
}

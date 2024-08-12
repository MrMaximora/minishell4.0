/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derey <derey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 08:47:13 by derey             #+#    #+#             */
/*   Updated: 2024/08/09 14:26:04 by derey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	proces(t_input *line, int fd, t_init *init_shell, int o)
{
	if (ft_strnstr(line->all_tokens[o], "cd", 3))
		cmd_cd(line, o + 1, init_shell);
	else if (ft_strnstr(line->all_tokens[o], "echo", 4))
		cmd_echo(line->all_tokens, o + 1, fd, init_shell);
	else if (ft_strnstr(line->all_tokens[o], "pwd", 3))
		cmd_pwd();
	else if (ft_strnstr(line->all_tokens[o], "export", 6))
		cmd_export(line->all_tokens, o + 1, init_shell);
	else if (ft_strnstr(line->all_tokens[o], "unset", 5))
		cmd_unset(line->all_tokens, o + 1, init_shell);
	else if (ft_strnstr(line->all_tokens[o], "env", 3))
		cmd_env(init_shell, fd);
	else if (ft_strnstr(line->all_tokens[o], "exit", 4))
		cmd_exit(line, o + 1, init_shell);
}

int	check_process(t_lexer_tab **tab_lexer, t_execute *process, t_input *line)
{
	t_lexer_tab	*current;

	current = *tab_lexer;
	while (current)
	{
		if (current->type != TOKEN_ARGS && current->type != TOKEN_SEMICOLON
			&& current->next == NULL && current->type
				!= TOKEN_BUILTIN && current->type != TOKEN_EXPAND)
		{
			ft_printf_error(" syntax error near unexpected token `%s' `%s'\n", current->arg, line->input);
			return (1);
		}
		if (current->next && current->type != TOKEN_REDIRECT_INPUT && current->type != TOKEN_REDIRECT_OUTPUT && current->type != TOKEN_APPEND  && current->next->type == TOKEN_ARGS && current->next->arg[0] == '.')
		{
				if (access(current->next->arg, F_OK) == 0)
					current->next->infile = 1;
				else
					current->next->infile = 2;
		}
		else if (current->index == 0 && current->type == TOKEN_PIPE)
		{
			ft_printf_error(" syntax error near unexpected token `%s' `%s'\n", current->arg, line->input);
			return (1);
		}
		if (current->type == TOKEN_PIPE)
			process->n_pipe++;
		current = current->next;
	}
	return (0);
}

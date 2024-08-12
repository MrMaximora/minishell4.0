/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derey <derey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:08:20 by derey             #+#    #+#             */
/*   Updated: 2024/07/23 14:57:38 by derey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_signal(int signa)
{
	if (signa == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("",0);
		rl_redisplay();
	}
	else if (signa == SIGQUIT)
		exit(0);
}
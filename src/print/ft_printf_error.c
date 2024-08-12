/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derey <derey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:09:19 by derey             #+#    #+#             */
/*   Updated: 2024/07/15 09:50:11 by derey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_check_error(const char *s, int i, va_list lst)
{
	if (s[i] == 'c')
		i = ft_putchar_i_error(va_arg(lst, int));
	else if (s[i] == 's')
		i = ft_putstr_i_error(va_arg(lst, char *));
	else if (s[i] == 'd' || s[i] == 'i')
		i = ft_putnbr_i_error(va_arg(lst, int));
	else if (s[i] == 'u')
		i = ft_putnbr_u_error(va_arg(lst, int));
	else if (s[i] == '%')
		i = ft_putchar_i_error('%');
	return (i);
}

int	ft_printf_error(const char *s, ...)
{
	int		i;
	int		len;
	va_list	lst;

	if (s == NULL)
		return (-42);
	va_start(lst, s);
	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			len += ft_check_error(s, i + 1, lst);
			i++;
		}
		else
			len += ft_putchar_i_error(s[i]);
		i++;
	}
	va_end(lst);
	return (len);
}

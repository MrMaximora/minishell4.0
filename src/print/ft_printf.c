/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derey <derey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:09:19 by derey             #+#    #+#             */
/*   Updated: 2024/07/15 09:50:22 by derey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check(const char *s, int i, va_list lst)
{
	if (s[i] == 'c')
		i = ft_putchar_i(va_arg(lst, int));
	else if (s[i] == 's')
		i = ft_putstr_i(va_arg(lst, char *));
	else if (s[i] == 'd' || s[i] == 'i')
		i = ft_putnbr_i(va_arg(lst, int));
	else if (s[i] == 'u')
		i = ft_putnbr_u(va_arg(lst, int));
	else if (s[i] == '%')
		i = ft_putchar_i('%');
	return (i);
}

int	ft_printf(const char *s, ...)
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
			len += ft_check(s, i + 1, lst);
			i++;
		}
		else
			len += ft_putchar_i(s[i]);
		i++;
	}
	va_end(lst);
	return (len);
}

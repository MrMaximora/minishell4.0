/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derey <derey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:54:00 by derey             #+#    #+#             */
/*   Updated: 2024/07/15 09:50:19 by derey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_putstr_i(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s[i] != '\0')
	{
		ft_putchar_i(s[i]);
		i++;
	}
	return (i);
}

int	ft_putchar_i(char c)
{
	write(1, &c, 1);
	return (1);
}

static long	ft_find_power(long nb)
{
	long	pow;

	pow = 1;
	while (nb / 10 != 0)
	{
		nb /= 10;
		pow *= 10;
	}
	return (pow);
}

int	ft_putnbr_i(int nb)
{
	int	pow;
	int	i;

	i = 0;
	pow = ft_find_power(nb);
	if (nb == -2147483648)
	{
		ft_putstr_i("-2147483648");
		return (11);
	}
	if (nb < 0)
	{
		ft_putchar_i('-');
		nb *= -1;
		i++;
	}
	while (pow >= 1)
	{
		ft_putchar_i((nb / pow) + '0');
		nb %= pow;
		pow /= 10;
		i++;
	}
	return (i);
}

int	ft_putnbr_u(unsigned int nb)
{
	int	pow;
	int	i;

	i = 0;
	pow = ft_find_power(nb);
	while (pow >= 1)
	{
		ft_putchar_i((nb / pow) + '0');
		nb %= pow;
		pow /= 10;
		i++;
	}
	return (i);
}

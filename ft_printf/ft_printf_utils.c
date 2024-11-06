/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 21:44:06 by aumoreno          #+#    #+#             */
/*   Updated: 2024/01/13 10:10:54 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *s)
{
	size_t	len;

	if (!s)
	{
		return (write(1, "(null)", 6));
	}
	len = ft_strlen(s);
	return (write(1, s, len));
}

int	ft_putnbr(int n)
{
	int	len;

	len = 0;
	if (n == -2147483648)
	{
		len += ft_putstr("-2147483648");
		return (len);
	}
	else if (n < 0)
	{
		len += ft_putchar('-');
		len += ft_putnbr(-n);
	}
	else if (n >= 10)
	{
		len += ft_putnbr(n / 10);
		len += ft_putchar(n % 10 + '0');
	}
	else
	{
		len += ft_putchar(n + '0');
	}
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 21:11:39 by aumoreno          #+#    #+#             */
/*   Updated: 2024/01/13 09:27:11 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_process_hex(int x, int n)
{
	int	len;

	len = 0;
	if (x <= 9)
	{
		len += ft_putchar(x + '0');
	}
	else
	{
		if (n == 1)
		{
			len += ft_putchar ((x - 10) + 'A');
		}
		else
		{
			len += ft_putchar ((x - 10) + 'a');
		}
	}
	return (len);
}

int	ft_put_hex(unsigned int x, unsigned int n)
{
	int	len;

	len = 0;
	if (x >= 16)
	{
		len += ft_put_hex (x / 16, n);
		len += ft_process_hex (x % 16, n);
	}
	else
	{
		len += ft_process_hex ((char)x, n);
	}
	return (len);
}

int	ft_print_hex(unsigned int x, unsigned int n)
{
	int	len;

	len = 0;
	if (x == 0)
	{
		len += write (1, "0", 1);
	}
	else
	{
		len = ft_put_hex (x, n);
	}
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 06:19:32 by aumoreno          #+#    #+#             */
/*   Updated: 2024/01/13 09:45:28 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_process_digit(int num)
{
	if (num <= 9)
	{
		ft_putchar(num + '0');
	}
	else
	{
		ft_putchar((num - 10) + 'a');
	}
}

void	ft_put_ptr(size_t ptr)
{
	if (ptr >= 16)
	{
		ft_put_ptr(ptr / 16);
		ft_put_ptr(ptr % 16);
	}
	else
	{
		ft_process_digit(ptr);
	}
}

int	ft_ptr_len(size_t ptr)
{
	int	len;

	len = 0;
	while (ptr != 0)
	{
		len++;
		ptr = ptr / 16;
	}
	return (len);
}

int	ft_print_ptr(unsigned long ptr)
{
	int	len;

	len = 0;
	len += write(1, "0x", 2);
	if (ptr == 0)
	{
		len += write(1, "0", 1);
	}
	else
	{
		ft_put_ptr(ptr);
		len += ft_ptr_len(ptr);
	}
	return (len);
}

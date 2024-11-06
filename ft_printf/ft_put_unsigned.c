/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:07:32 by aumoreno          #+#    #+#             */
/*   Updated: 2024/01/13 09:27:44 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_unsigned(unsigned int u)
{
	int	len;

	len = 0;
	if (u <= 9)
	{
		len += ft_putchar(u + '0');
	}
	else
	{
		len += ft_put_unsigned(u / 10);
		len += ft_put_unsigned(u % 10);
	}
	return (len);
}

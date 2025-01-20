/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 09:27:57 by aumoreno          #+#    #+#             */
/*   Updated: 2025/01/20 12:11:34 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdio.h> 
# include <stdarg.h>
# include <stdint.h>

int		ft_printf(char const *format, ...);
int		ft_print_hex(unsigned int x, unsigned int n);
int		ft_print_ptr(unsigned long ptr);
int		ft_put_unsigned(unsigned int u);
size_t	ft_strlen_printf(const char *s);
int		ft_putchar(int c);
int		ft_putstr(char *s);
int		ft_putnbr(int n);

#endif
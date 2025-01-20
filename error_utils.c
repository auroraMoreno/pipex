/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:36:24 by aumoreno          #+#    #+#             */
/*   Updated: 2025/01/18 11:38:03 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_error(char *err_msg)
{
    write(STDERR_FILENO,err_msg,sizeof(err_msg)); //CAMBIAR ESTO A ALGO MÁS BONITO
    exit(EXIT_FAILURE);  
}
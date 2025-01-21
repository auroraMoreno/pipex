/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:36:24 by aumoreno          #+#    #+#             */
/*   Updated: 2025/01/21 10:49:41 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_error(char *err_msg)
{
    //write(STDERR_FILENO,err_msg,sizeof(err_msg)); //CAMBIAR ESTO A ALGO MÁS BONITO
    perror(err_msg);
    exit(EXIT_FAILURE);  
}
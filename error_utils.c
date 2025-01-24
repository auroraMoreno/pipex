/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:36:24 by aumoreno          #+#    #+#             */
/*   Updated: 2025/01/24 11:24:24 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *err_msg)
{
	perror(err_msg);
	exit(EXIT_FAILURE);
}

void	ft_cmd_error(char *cmd)
{
	ft_putstr_fd("Command not found: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
}

void	ft_args_error(void)
{
	ft_putstr_fd("Error in provided arguments: ", STDERR_FILENO);
	ft_putstr_fd("Try: ./pipex infile command1 command2 outfile", 2);
	write(STDERR_FILENO, "\n", 1);
}

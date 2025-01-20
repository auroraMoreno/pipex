/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:33:15 by aumoreno          #+#    #+#             */
/*   Updated: 2025/01/20 10:46:04 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf/ft_printf.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

void ft_error(char* err_msg);
//int ft_check_args_order(char* argv);
int ft_check_file_permissions(char *infile, char *outfile);
int ft_check_bin(char *cmd1, char *cmd2, char **envp);
char *ft_find_path(char **envp);






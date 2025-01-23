/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:33:15 by aumoreno          #+#    #+#             */
/*   Updated: 2025/01/23 11:57:53 by aumoreno         ###   ########.fr       */
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

#define READ_END 0
#define WRITE_END 1

void ft_error(char* err_msg);
int ft_check_file_permissions(char *infile, char *outfile);
char *ft_check_bin(char *cmd, char **envp);
char *ft_find_path_variable(char **envp);
char *ft_find_cmd_paths(char *cmd, char **envp);
int ft_creating_processes(char** argv, char** envp, char **cmd_paths);
void ft_handle_child(int* fd, char** argv, char* cmd_path, char** envp);
char *ft_format_path(char *path, char *cmd);
void ft_free_cmds(char **cmd_to_free);

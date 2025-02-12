/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:36:24 by aumoreno          #+#    #+#             */
/*   Updated: 2025/02/12 12:16:10 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *err_msg) // add error code 2 girly
{
	ft_putstr_fd(err_msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	ft_process_error(char *msg, char **paths, int error_code)
{
	ft_free_cmds(paths);
	perror(msg);
	exit(error_code);
}

void	ft_file_error(char *msg, char **cmd, char *cmd_path)
{
	free(cmd_path);
	ft_free_cmds(cmd);
	ft_error(msg);
}

void	ft_cmd_error(char **cmd_paths, char **cmd1, char **cmd2)
{
	char	*cmd;

	if (cmd_paths[0] == 0)
		cmd = cmd1[0];
	else
		cmd = cmd2[0];
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	ft_free_paths(cmd_paths);
	ft_free_cmds(cmd1);
	ft_free_cmds(cmd2);
	exit(127);
}

void	ft_args_error(void)
{
	ft_putstr_fd(ERROR_ARGS, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

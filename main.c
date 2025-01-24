/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 10:14:12 by aumoreno          #+#    #+#             */
/*   Updated: 2025/01/24 12:42:09 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_check_file_permissions(char *infile, char *outfile)
{
	if (access(infile, F_OK) == -1 || access(outfile, F_OK) == -1)
		return (-1);
	if (access(infile, R_OK) == -1)
		return (-1);
	if (access(outfile, W_OK) == -1)
		return (-1);
	return (0);
}

char	*ft_check_bin(char *cmd, char **envp)
{
	char	**path;
	char	*path_cmd;
	int		i;

	path = ft_split(ft_find_path_variable(envp), ':');
	if (!path)
		return (0);
	if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
		return (cmd);
	path_cmd = NULL;
	i = 0;
	while (path[i])
	{
		path_cmd = ft_format_path(path[i], cmd);
		if (access(path_cmd, F_OK) == 0 && access(path_cmd, X_OK) == 0)
			break ;
		free(path_cmd);
		path_cmd = NULL;
		i++;
	}
	ft_free_cmds(path);
	if (!path_cmd)
		return (0);
	return (path_cmd);
}

int	main(int argc, char **argv, char **envp)
{
	char	**cmd1;
	char	**cmd2;
	char	**cmd_paths;

	if (argc == 5)
	{
		if (ft_check_file_permissions(argv[1], argv[4]) == -1)
			ft_error("Error in files: ");
		cmd1 = ft_split(argv[2], ' ');
		cmd2 = ft_split(argv[3], ' ');
		cmd_paths = ft_calloc(sizeof(char *), 2);
		cmd_paths[0] = ft_check_bin(cmd1[0], envp);
		cmd_paths[1] = ft_check_bin(cmd2[0], envp);
		if (cmd_paths[0] == 0)
			ft_cmd_error(cmd1[0]);
		if (cmd_paths[1] == 0)
			ft_cmd_error(cmd2[0]);
		ft_creating_processes(argv, envp, cmd_paths);
		ft_free_cmds(cmd1);
		ft_free_cmds(cmd2);
		ft_free_paths(cmd_paths);
	}
	else
		ft_args_error();
	return (0);
}

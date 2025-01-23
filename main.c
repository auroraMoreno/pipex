/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 10:14:12 by aumoreno          #+#    #+#             */
/*   Updated: 2025/01/23 14:25:54 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_check_file_permissions(char *infile, char *outfile)
{
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
		if (access(argv[1], F_OK) == -1 || access(argv[4], F_OK) == -1)
			ft_error("Path does not exist in file system.\n");
		if (ft_check_file_permissions(argv[1], argv[4]) == -1)
			ft_error("Check file permissions.\n");
		cmd1 = ft_split(argv[2], ' ');
		cmd2 = ft_split(argv[3], ' ');
		cmd_paths = ft_calloc(sizeof(char *), 2);
		cmd_paths[0] = ft_check_bin(cmd1[0], envp);
		cmd_paths[1] = ft_check_bin(cmd2[0], envp);
		if (cmd_paths[0] == 0 || cmd_paths[1] == 0)
			ft_error("Bin does not exist or does not have the right permissions\n");
		ft_creating_processes(argv, envp, cmd_paths);
		ft_free_cmds(cmd1);
		ft_free_cmds(cmd2);
		free(cmd_paths[0]);
		free(cmd_paths[1]);
		free(cmd_paths);
	}
	else
		ft_error("Check the given arguments.");
	return (0);
}

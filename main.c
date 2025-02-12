/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 10:14:12 by aumoreno          #+#    #+#             */
/*   Updated: 2025/02/12 12:05:35 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_free_main(char **cmd1, char **cmd2, char **cmd_paths)
{
	ft_free_cmds(cmd1);
	ft_free_cmds(cmd2);
	ft_free_paths(cmd_paths);
	return (0);
}

char	*ft_check_bin(char *cmd, char **envp)
{
	char	**path;
	char	*path_cmd;
	int		i;

	if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path = ft_split(ft_find_path_variable(envp), ':');
	if (!path)
	{
		ft_free_cmds(path);
		return (0);
	}
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
	return (path_cmd);
}

int	main(int argc, char **argv, char **envp)
{
	char	**cmd1;
	char	**cmd2;
	char	**cmd_paths;

	if (argc != 5)
		ft_args_error();
	cmd1 = ft_split(argv[2], ' ');
	cmd2 = ft_split(argv[3], ' ');
	if (!cmd1 || !cmd2)
		ft_free_both_cmd(cmd1, cmd2);
	cmd_paths = ft_calloc(sizeof(char *), 2);
	if (!cmd_paths)
	{
		ft_free_main(cmd1, cmd2, cmd_paths);
		ft_error(ERROR_MALLOC);
	}
	cmd_paths[0] = ft_check_bin(cmd1[0], envp);
	cmd_paths[1] = ft_check_bin(cmd2[0], envp);
	if (cmd_paths[0] == 0 || cmd_paths[1] == 0)
		ft_cmd_error(cmd_paths, cmd1, cmd2);
	ft_free_cmds(cmd1);
	ft_free_cmds(cmd2);
	ft_creating_processes(argv, envp, cmd_paths);
	ft_free_paths(cmd_paths);
	return (0);
}

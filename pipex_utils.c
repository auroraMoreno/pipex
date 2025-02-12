/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:26:01 by aumoreno          #+#    #+#             */
/*   Updated: 2025/02/12 10:58:34 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_find_path_variable(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (&envp[i][5]);
		i++;
	}
	return (0);
}

char	*ft_format_path(char *path, char *cmd)
{
	char	*formatted_path;
	char	*aux;

	aux = ft_strjoin(path, "/");
	formatted_path = ft_strjoin(aux, cmd);
	free(aux);
	return (formatted_path);
}

void	ft_free_cmds(char **cmd_to_free)
{
	int	i;

	i = 0;
	while (cmd_to_free[i])
	{
		free(cmd_to_free[i]);
		i++;
	}
	free(cmd_to_free);
}

void	ft_free_paths(char **paths)
{
	if (paths[0])
		free(paths[0]);
	if (paths[1])
		free(paths[1]);
	free(paths);
}

void	ft_free_both_cmd(char **cmd1, char **cmd2)
{
	ft_free_cmds(cmd1);
	ft_free_cmds(cmd2);
	ft_error("Error getting the command.\n");
}

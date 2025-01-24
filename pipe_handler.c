/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:35:56 by aumoreno          #+#    #+#             */
/*   Updated: 2025/01/24 12:28:16 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_handle_child(int *fd, char **argv, char *cmd_path, char **envp)
{
	int		infile_fd;
	char	**cmd1;
	char	*infile_path;

	infile_path = argv[1];
	cmd1 = ft_split(argv[2], ' ');
	close(fd[READ_END]);
	infile_fd = open(infile_path, O_RDONLY, 0777);
	if (infile_fd == -1)
		ft_error("Error in opening file: ");
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	dup2(fd[WRITE_END], STDOUT_FILENO);
	close(fd[WRITE_END]);
	if (execve(cmd_path, cmd1, envp) < 0)
		ft_error("Error executing process: ");
	ft_free_cmds(cmd1);
}

void	ft_handle_parent(int *fd, char **argv, char *cmd_path, char **envp)
{
	char	**cmd2;
	char	*outfile_path;
	pid_t	pid;
	int		outfile_fd;

	outfile_path = argv[4];
	cmd2 = ft_split(argv[3], ' ');
	pid = fork();
	close(fd[WRITE_END]);
	if (pid == -1)
		ft_error("Error creating process: ");
	else if (pid == 0)
	{
		outfile_fd = open(outfile_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (outfile_fd == -1)
			ft_error("Error in opening file: ");
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[READ_END]);
		dup2(outfile_fd, STDOUT_FILENO);
		if (execve(cmd_path, cmd2, envp) < 0)
			ft_error("Error executing process: ");
		ft_free_cmds(cmd2);
	}
	else
	{
		close(fd[READ_END]);
		ft_free_cmds(cmd2);
	}
}

int	ft_creating_processes(char **argv, char **envp, char **cmd_paths)
{
	pid_t	pid;
	int		fd1[2];
	int		status;

	if (pipe(fd1) == -1)
		ft_error("Error creating pipe: ");
	pid = fork();
	if (pid == -1)
		ft_error("Error creating process: ");
	else if (pid == 0)
		ft_handle_child(fd1, argv, cmd_paths[0], envp);
	else
		ft_handle_parent(fd1, argv, cmd_paths[1], envp);
	waitpid(pid, &status, WNOHANG);
	waitpid(pid, &status, WNOHANG);
	return (status);
}

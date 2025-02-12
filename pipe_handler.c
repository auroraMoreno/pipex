/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:35:56 by aumoreno          #+#    #+#             */
/*   Updated: 2025/02/12 11:17:05 by aumoreno         ###   ########.fr       */
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
	if (!cmd1)
	{
		ft_free_cmds(cmd1);
		free(cmd_path);
		ft_error(ERROR_MALLOC);
	}
	infile_fd = open(infile_path, O_RDONLY);
	if (infile_fd == -1)
		ft_file_error(ERROR_FILE, cmd1, cmd_path);
	close(fd[READ_END]);
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	dup2(fd[WRITE_END], STDOUT_FILENO);
	close(fd[WRITE_END]);
	if (execve(cmd_path, cmd1, envp) < 0)
		ft_file_error(ERROR_EXE, cmd1, cmd_path);
	ft_free_cmds(cmd1);
}

void	ft_handle_parent(int *fd, char **argv, char *cmd_path, char **envp)
{
	char	**cmd2;
	char	*outfile_path;
	int		outfile_fd;

	outfile_path = argv[4];
	cmd2 = ft_split(argv[3], ' ');
	if (!cmd2)
	{
		ft_free_cmds(cmd2);
		free(cmd_path);
		ft_error(ERROR_MALLOC);
	}
	outfile_fd = open(outfile_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
		ft_file_error(ERROR_FILE, cmd2, cmd_path);
	close(fd[WRITE_END]);
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	if (execve(cmd_path, cmd2, envp) < 0)
		ft_file_error(ERROR_EXE, cmd2, cmd_path);
	ft_free_cmds(cmd2);
}

void	ft_creating_processes(char **argv, char **envp, char **cmd_paths)
{
	pid_t	pid_parent;
	pid_t	pid_child;
	int		fd1[2];

	if (pipe(fd1) == -1)
		ft_process_error(ERROR_PIPE, cmd_paths, errno);
	pid_child = fork();
	if (pid_child < 0)
		ft_process_error(ERROR_FORK, cmd_paths, errno);
	if (pid_child == 0)
		ft_handle_child(fd1, argv, cmd_paths[0], envp);
	pid_parent = fork();
	if (pid_parent < 0)
		ft_process_error(ERROR_FORK, cmd_paths, errno);
	if (pid_parent == 0)
		ft_handle_parent(fd1, argv, cmd_paths[1], envp);
	close(fd1[0]);
	close(fd1[1]);
	waitpid(pid_child, NULL, 0);
	waitpid(pid_parent, NULL, 0);
	return ;
}

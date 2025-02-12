/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:33:15 by aumoreno          #+#    #+#             */
/*   Updated: 2025/02/12 11:00:56 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>

# ifndef READ_END
#  define READ_END 0
# endif

# ifndef WRITE_END
#  define WRITE_END 1
# endif

/**SOME ERROR MESSAGES */

# ifndef ERROR_ARGS
#  define ERROR_ARGS "Wrong arguments:\n./pipex <input> <cmd1> <cm2> <output>\n"
# endif

# ifndef ERROR_MALLOC
#  define ERROR_MALLOC "Failed memory alocation.\n"
# endif

# ifndef ERROR_PIPE
#  define ERROR_PIPE "Error creating pipe.\n"
# endif

# ifndef ERROR_FORK
#  define ERROR_FORK "Error creating subprocess.\n"
# endif

# ifndef ERROR_FILE
#  define ERROR_FILE "Error in file.\n"
# endif

# ifndef ERROR_EXE
#  define ERROR_EXE "Error in executng commands.\n"
# endif

char	*ft_check_bin(char *cmd, char **envp);
char	*ft_find_path_variable(char **envp);
char	*ft_find_cmd_paths(char *cmd, char **envp);
char	*ft_format_path(char *path, char *cmd);
int		ft_check_file_permissions(char *infile, char *outfile);
void	ft_creating_processes(char **argv, char **envp, char **cmd_paths);
void	ft_handle_child(int *fd, char **argv, char *cmd_path, char **envp);
void	ft_handle_parent(int *fd, char **argv, char *cmd_path, char **envp);
void	ft_free_cmds(char **cmd_to_free);
void	ft_free_paths(char **paths);
int		ft_free_main(char	**cmd1, char **cmd2, char **cmd_paths);
void	ft_free_both_cmd(char **cmd1, char **cmd2);
void	ft_error(char *err_msg);
void	ft_cmd_error(char *cmd, char **cmd_paths, char **cmd1, char **cmd2);
void	ft_process_error(char *msg, char **paths, int error_code);
void	ft_file_error(char *msg, char **cmd, char *cmd_path);
void	ft_args_error(void);
#endif
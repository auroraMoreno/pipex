/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:58:16 by aumoreno          #+#    #+#             */
/*   Updated: 2024/11/06 19:33:52 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_new_line(char *stash)
{
	char	*line;
	char	*p_len;
	int		break_pos;

	p_len = ft_strchr_gnl(stash, '\n');
	break_pos = p_len - stash + 1;
	line = ft_substr_gnl(stash, 0, break_pos);
	if (!line)
		return (NULL);
	return (line);
}

char	*ft_clean_stash(char *stash)
{
	char	*clean_stash;
	char	*aux;
	int		break_pos;

	aux = ft_strchr_gnl(stash, '\n');
	if (!aux)
	{
		clean_stash = NULL;
		return (ft_free(&stash));
	}
	else
	{
		break_pos = (aux - stash) + 1;
	}
	if (!stash[break_pos])
		return (ft_free(&stash));
	clean_stash = ft_substr_gnl(stash, break_pos, ft_strlen_gnl(stash) - break_pos);
	ft_free(&stash);
	if (!clean_stash)
		return (NULL);
	return (clean_stash);
}

char	*ft_read_line(int fd, char *stash)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free(&stash));
	buffer[0] = '\0';
	bytes_read = 1;
	while (!ft_strchr_gnl(buffer, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			stash = ft_strjoin_gnl(stash, buffer);
		}
	}
	free(buffer);
	if (bytes_read == -1)
		return (ft_free(&stash));
	return (stash);
}

char	*ft_free(char **stash)
{
	free(*stash);
	*stash = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if ((stash && !ft_strchr_gnl(stash, '\n')) || !stash)
		stash = ft_read_line(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_get_new_line(stash);
	if (!line)
		return (ft_free(&stash));
	stash = ft_clean_stash(stash);
	return (line);
}

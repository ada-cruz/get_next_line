/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cruz <ada-cruz@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:41:07 by ada-cruz          #+#    #+#             */
/*   Updated: 2022/10/06 19:13:40 by ada-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	ft_strchr(const char *s, char c)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			return (1);
		i++;
	}
	if ((unsigned char)c == '\0')
	{
		return (1);
	}
	return (0);
}

static char	*get_buffer(int fd, char *buffer)
{
	char	*tmp;
	ssize_t	read_bytes;

	tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (NULL);
	read_bytes = 1;
	while (ft_strchr(buffer, '\n') == 0)
	{
		read_bytes = read(fd, tmp, BUFFER_SIZE);
		if (read_bytes == 0 || read_bytes == -1)
			break ;
		tmp[read_bytes] = '\0';
		buffer = ft_strjoin(buffer, tmp);
		if (buffer == NULL)
		{
			free(tmp);
			return (NULL);
		}
	}
	free(tmp);
	if (read_bytes == -1)
		return (NULL);
	return (buffer);
}

static char	*get_line(char *buffer)
{
	char	*line;
	size_t	i;

	i = 0;
	if (buffer[i] == '\0')
		return (NULL);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	line = malloc(sizeof(char) * (i + (buffer[i] == '\n') + 1));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*preparenl(char *buffer)
{
	char	*next;
	size_t	i;
	size_t	j;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	next = malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (!next)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i + j] != '\0')
	{
		next[j] = buffer[i + j];
		j++;
	}
	next[j] = '\0';
	free(buffer);
	return (next);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = get_buffer(fd, buffer[fd]);
	if (buffer[fd] == NULL)
		return (NULL);
	line = get_line(buffer[fd]);
	buffer[fd] = preparenl(buffer[fd]);
	return (line);
}

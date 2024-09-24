/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaakson <alaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:46:00 by alaakson          #+#    #+#             */
/*   Updated: 2024/09/11 11:45:37 by alaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*line_extract(char *line)
{
	size_t	length;
	char	*storage;

	if (!line)
		return (NULL);
	length = 0;
	while (line[length] != '\n' && line[length] != '\0')
		length++;
	if (line[length] == '\0')
		return (NULL);
	storage = ft_strdup(line + length + 1);
	if (!storage)
		return (NULL);
	line[length + 1] = '\0';
	return (storage);
}

static char	*length_of_fd(int fd, char *buf, char *storage)
{
	char	*temp;
	int		read_lines;

	read_lines = 1;
	while (read_lines > 0)
	{
		read_lines = read(fd, buf, BUFFER_SIZE);
		if (read_lines == -1)
			return (NULL);
		else if (read_lines == 0)
			break ;
		buf[read_lines] = '\0';
		if (!storage)
			storage = ft_strdup("");
		temp = storage;
		storage = ft_strjoin(temp, buf);
		freedom (&temp);
		if (!storage)
			return (NULL);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*content;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		freedom (&content);
		return (NULL);
	}
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	line = length_of_fd(fd, buffer, content);
	freedom (&buffer);
	if (!line || line[0] == '\0')
	{
		freedom (&content);
		return (NULL);
	}
	content = line_extract(line);
	if (content && content[0] == '\0')
		freedom (&content);
	return (line);
}

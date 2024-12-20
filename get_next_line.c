/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamachi <klamachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 08:22:48 by klamachi          #+#    #+#             */
/*   Updated: 2024/12/11 12:26:58 by klamachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*fullbuffer(void)
{
	char	*buffer;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	return (buffer);
}

static char	*join(char *reminder, char *buffer)
{
	char	*tmp;

	tmp = reminder;
	reminder = ft_strjoin(reminder, buffer);
	if (!reminder)
		return (free(tmp), free(buffer), NULL);
	free(tmp);
	return (reminder);
}

static char	*fullreminder(char *reminder, int fd)
{
	char	*buffer;
	ssize_t	resread;

	resread = 1;
	buffer = fullbuffer();
	if (!buffer || BUFFER_SIZE <= 0)
		return (NULL);
	while (resread > 0)
	{
		resread = read(fd, buffer, BUFFER_SIZE);
		if (resread == -1)
			return (free(buffer), free(reminder), NULL);
		if (resread == 0)
			break ;
		buffer[resread] = '\0';
		if (!reminder)
			reminder = ft_strdup("");
		reminder = join(reminder, buffer);
		if (!reminder)
			return (free(buffer), NULL);
		if (ft_strchr(reminder, '\n'))
			break ;
	}
	return (free(buffer), reminder);
}

char	*get_next_line(int fd)
{
	static char	*reminder;
	char		*line;
	char		*pos;
	char		*tmp;

	reminder = fullreminder(reminder, fd);
	if (!reminder)
		return (NULL);
	pos = ft_strchr(reminder, '\n');
	if (pos != NULL)
	{
		line = ft_substr(reminder, 0, (pos - reminder + 1));
		if (!line)
			return (free(reminder), NULL);
		tmp = ft_strdup(pos + 1);
		free(reminder);
		return (reminder = tmp, line);
	}
	line = reminder;
	reminder = NULL;
	if (*line == '\0')
		return (free(line), NULL);
	return (line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjakowic <mjakowic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:35:13 by mjakowic          #+#    #+#             */
/*   Updated: 2024/03/20 17:44:58 by mjakowic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_jaf(char *buffer, const char *buf)
{
	char	*tempo;

	tempo = ft_strjoin(buffer, buf);
	free(buffer);
	return (tempo);
}

static char	*ft_trim_buffer(char *buffer)
{
	int		i;
	int		j;
	char	*new_buffer;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	i++;
	new_buffer = ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
	if (!new_buffer)
		return (NULL);
	while (buffer[i] != '\0')
	{
		new_buffer[j] = buffer[i];
		i++;
		j++;
	}
	free(buffer);
	return (new_buffer);
}

static char	*ft_ext_line(char *buffer)
{
	char	*line;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (buffer[len] && buffer[len] != '\n')
		len++;
	if (buffer[len] == '\n')
		len++;
	line = ft_calloc(len + 1, sizeof(char));
	if (!line)
		return (NULL);
	while (i < len)
	{
		line[i] = buffer[i];
		i++;
	}
	return (line);
}

static char	*read_until_nl_or_eof(int fd, char *res)
{
	char	*buffer;
	int		bytes_read;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		res = ft_jaf(res, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (bytes_read == -1)
	{
		free(res);
		return (NULL);
	}
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
		buffer = ft_calloc(1, sizeof(char));
	buffer = read_until_nl_or_eof(fd, buffer);
	if (!buffer || !*buffer)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = ft_ext_line(buffer);
	buffer = ft_trim_buffer(buffer);
	return (line);
}

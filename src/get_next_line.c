/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:44:13 by asezgin           #+#    #+#             */
/*   Updated: 2025/03/17 11:44:14 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

static char	*ft_read_file(int fd, char *save_str)
{
	char	*buffer;
	char	*temp;
	int		read_bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (read_bytes > 0 && !gnl_strchr(save_str, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		temp = save_str;
		save_str = gnl_strjoin(save_str, buffer);
		free(temp);
		if (!save_str)
			break ;
	}
	free(buffer);
	return (save_str);
}

static char	*ft_get_line(char *save_str)
{
	char	*line;
	int		i;

	i = 0;
	if (!save_str || !save_str[0])
		return (NULL);
	while (save_str[i] && save_str[i] != '\n')
		i++;
	if (save_str[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (save_str[i] && save_str[i] != '\n')
	{
		line[i] = save_str[i];
		i++;
	}
	if (save_str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*ft_save_remaining(char *save_str)
{
	char	*new_save;
	int		i;
	int		j;

	i = 0;
	while (save_str[i] && save_str[i] != '\n')
		i++;
	if (!save_str[i])
	{
		free(save_str);
		return (NULL);
	}
	new_save = malloc(sizeof(char) * (gnl_strlen(save_str) - i + 1));
	if (!new_save)
	{
		free(save_str);
		return (NULL);
	}
	i++;
	j = 0;
	while (save_str[i])
		new_save[j++] = save_str[i++];
	new_save[j] = '\0';
	free(save_str);
	return (new_save);
}

char	*get_next_line(int fd)
{
	static char	*save_str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!save_str)
		save_str = gnl_calloc(1, 1);
	save_str = ft_read_file(fd, save_str);
	if (!save_str)
		return (NULL);
	line = ft_get_line(save_str);
	save_str = ft_save_remaining(save_str);
	return (line);
}

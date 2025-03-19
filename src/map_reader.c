/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:44:00 by asezgin           #+#    #+#             */
/*   Updated: 2025/03/19 08:24:45 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int	get_height(char *filename)
{
	int		fd;
	int		height;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

static int	get_width(char *filename)
{
	int		fd;
	char	*line;
	int		width;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (0);
	}
	width = count_words(line);
	free(line);
	close(fd);
	return (width);
}

static void	process_line(t_map *map, char **split, int i)
{
	int	j;

	j = 0;
	while (j < map->width && split[j])
	{
		map->points[i][j].x = j;
		map->points[i][j].y = i;
		set_point_values(&map->points[i][j], split[j]);
		j++;
	}
	j = 0;
	while (split[j])
	{
		free(split[j]);
		j++;
	}
	free(split);
}

static void	fill_map_points(t_map *map, int fd)
{
	char	*line;
	char	**split;
	int		i;

	i = 0;
	while (i < map->height)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		split = ft_split(line, ' ');
		free(line);
		if (!split)
			break ;
		process_line(map, split, i);
		i++;
	}
}

t_map	*read_map(char *filename)
{
	t_map	*map;
	int		fd;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->height = get_height(filename);
	map->width = get_width(filename);
	if (map->height <= 0 || map->width <= 0)
	{
		free(map);
		return (NULL);
	}
	if (!allocate_map_points(map))
	{
		free(map);
		return (NULL);
	}
	fd = open(filename, O_RDONLY);
	fill_map_points(map, fd);
	close(fd);
	return (map);
}

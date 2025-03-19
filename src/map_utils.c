/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:43:55 by asezgin           #+#    #+#             */
/*   Updated: 2025/03/19 08:24:58 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	count_words(char *line)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (line[i])
			count++;
		while (line[i] && line[i] != ' ')
			i++;
	}
	return (count);
}

void	set_point_values(t_point *point, char *str)
{
	char	*comma;

	comma = ft_strchr(str, ',');
	if (comma)
	{
		*comma = '\0';
		point->color = ft_atoi_base(comma + 1, 16);
	}
	else
		point->color = 0xFFFFFF;
	point->z = ft_atoi(str);
}

int	allocate_map_points(t_map *map)
{
	int	i;

	map->points = (t_point **)malloc(sizeof(t_point *) * map->height);
	if (!map->points)
		return (0);
	i = 0;
	while (i < map->height)
	{
		map->points[i] = (t_point *)malloc(sizeof(t_point) * map->width);
		if (!map->points[i])
		{
			while (--i >= 0)
				free(map->points[i]);
			free(map->points);
			return (0);
		}
		i++;
	}
	return (1);
}

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->points)
	{
		i = 0;
		while (i < map->height)
		{
			if (map->points[i])
				free(map->points[i]);
			i++;
		}
		free(map->points);
	}
	free(map);
}

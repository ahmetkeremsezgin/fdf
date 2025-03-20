/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:43:35 by asezgin           #+#    #+#             */
/*   Updated: 2025/03/20 15:09:52 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include "../minilibx-linux/mlx.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	res;

	i = 0;
	neg = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * neg);
}

void	ft_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(1);
}

double	get_max_height(t_map *map)
{
	int		x;
	int		y;
	double	max_height;

	max_height = map->points[0][0].z;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->points[y][x].z > max_height)
				max_height = map->points[y][x].z;
			x++;
		}
		y++;
	}
	return (max_height);
}

double	get_min_height(t_map *map)
{
	int		x;
	int		y;
	double	min_height;

	min_height = map->points[0][0].z;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->points[y][x].z < min_height)
				min_height = map->points[y][x].z;
			x++;
		}
		y++;
	}
	return (min_height);
}

void	exit_program(t_fdf *fdf)
{
	if (!fdf)
		exit(0);
	if (fdf->img.img_ptr)
	{
		mlx_destroy_image(fdf->mlx_ptr, fdf->img.img_ptr);
		fdf->img.img_ptr = NULL;
	}
	if (fdf->win_ptr)
	{
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
		fdf->win_ptr = NULL;
	}
	if (fdf->map)
	{
		free_map(fdf->map);
		fdf->map = NULL;
	}
	if (fdf->mlx_ptr)
	{
		mlx_destroy_display(fdf->mlx_ptr);
		free(fdf->mlx_ptr);
		fdf->mlx_ptr = NULL;
	}
	free(fdf);
	exit(0);
}

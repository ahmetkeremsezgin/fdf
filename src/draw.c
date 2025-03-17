/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by user42            #+#    #+#             */
/*   Updated: 2025/03/17 09:59:28 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** Haritanın ölçek faktörünü hesaplar
*/
static float	get_scale_factor(t_map *map)
{
	float	scale_x;
	float	scale_y;
	int		map_width;
	int		map_height;
	float	scale;

	map_width = (map->width + map->height) * 0.5;
	map_height = (map->width + map->height) * 0.5 * 1.5;
	scale_x = (float)(WIN_WIDTH * 0.75) / map_width;
	scale_y = (float)(WIN_HEIGHT * 0.75) / map_height;
	if (scale_x < scale_y)
		scale = scale_x;
	else
		scale = scale_y;
	if (scale < 1)
		return (scale);
	if (scale > 30)
		return (30);
	return (scale);
}

/*
** İzometrik projeksiyon hesaplar
*/
static void	calculate_iso(t_point_iso *p, t_point p1, t_point p2, float scale)
{
	p->iso_x1 = (p1.x - p1.y) * scale;
	p->iso_y1 = (p1.x + p1.y - p1.z) * (scale / 2);
	p->iso_x2 = (p2.x - p2.y) * scale;
	p->iso_y2 = (p2.x + p2.y - p2.z) * (scale / 2);
	p->iso_x1 += WIN_WIDTH / 2;
	p->iso_y1 += WIN_HEIGHT / 2;
	p->iso_x2 += WIN_WIDTH / 2;
	p->iso_y2 += WIN_HEIGHT / 2;
}

/*
** Bresenham algoritması için delta ve adım hesaplar
*/
static void	calculate_delta(t_delta *d, t_point_iso *p)
{
	d->dx = p->iso_x2 - p->iso_x1;
	d->dy = p->iso_y2 - p->iso_y1;
	if (fabs(d->dx) > fabs(d->dy))
		d->step = fabs(d->dx);
	else
		d->step = fabs(d->dy);
	d->dx /= d->step;
	d->dy /= d->step;
}

/*
** İki nokta arasında çizgi çizer
*/
void	draw_line(t_point p1, t_point p2, t_fdf *fdf)
{
	t_point_iso	iso;
	t_delta		delta;
	float		x;
	float		y;
	float		scale;

	scale = get_scale_factor(fdf->map);
	calculate_iso(&iso, p1, p2, scale);
	calculate_delta(&delta, &iso);
	x = iso.iso_x1;
	y = iso.iso_y1;
	while ((int)(x - iso.iso_x2) || (int)(y - iso.iso_y2))
	{
		put_pixel(fdf, x, y, p1.color);
		x += delta.dx;
		y += delta.dy;
	}
}

/*
** Haritayı ekrana çizer
*/
void	draw_map(t_fdf *fdf)
{
	int	x;
	int	y;

	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			if (x < fdf->map->width - 1)
				draw_line(fdf->map->points[y][x],
					fdf->map->points[y][x + 1], fdf);
			if (y < fdf->map->height - 1)
				draw_line(fdf->map->points[y][x],
					fdf->map->points[y + 1][x], fdf);
			x++;
		}
		y++;
	}
}

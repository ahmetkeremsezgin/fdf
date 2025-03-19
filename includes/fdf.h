/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:44:37 by asezgin           #+#    #+#             */
/*   Updated: 2025/03/19 08:23:38 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "get_next_line.h"

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define KEY_ESC 65307

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_map
{
	int		width;
	int		height;
	t_point	**points;
}	t_map;

typedef struct s_fdf
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_map	*map;
}	t_fdf;

typedef struct s_point_iso
{
	int	iso_x1;
	int	iso_y1;
	int	iso_x2;
	int	iso_y2;
}	t_point_iso;

typedef struct s_delta
{
	float	dx;
	float	dy;
	float	step;
}	t_delta;

t_map	*read_map(char *filename);
void	free_map(t_map *map);
int		count_words(char *line);
void	set_point_values(t_point *point, char *str);
int		allocate_map_points(t_map *map);

void	draw_map(t_fdf *fdf);
void	draw_line(t_point p1, t_point p2, t_fdf *fdf);

int		ft_atoi(const char *str);
int		ft_atoi_base(const char *str, int base);
char	**ft_split(char const *s, char c);
void	ft_error(char *msg);
int		key_hook(int keycode, t_fdf *fdf);
int		close_window(t_fdf *fdf);
char	*ft_strchr(const char *s, int c);
void	put_pixel(t_fdf *fdf, int x, int y, int color);
double	get_min_height(t_map *map);
double	get_max_height(t_map *map);

void	setup_window(t_fdf *fdf);

#endif 
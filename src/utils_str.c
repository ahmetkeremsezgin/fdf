/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:43:42 by asezgin           #+#    #+#             */
/*   Updated: 2025/03/19 08:25:23 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <stdlib.h>

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

int	ft_atoi_base(const char *str, int base)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		i = 2;
	else if (str[0] == '#')
		i = 1;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = result * base + (str[i] - '0');
		else if (str[i] >= 'A' && str[i] <= 'F')
			result = result * base + (str[i] - 'A' + 10);
		else if (str[i] >= 'a' && str[i] <= 'f')
			result = result * base + (str[i] - 'a' + 10);
		else
			break ;
		i++;
	}
	return (result * sign);
}

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

void	put_pixel(t_fdf *fdf, int x, int y, int color)
{
	char	*pixel;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		pixel = fdf->img.addr + (y * fdf->img.line_length
				+ x * (fdf->img.bits_per_pixel / 8));
		*(unsigned int *)pixel = color;
	}
}

int	check_file_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (filename[len - 4] != '.' || filename[len - 3] != 'f'
		|| filename[len - 2] != 'd' || filename[len - 1] != 'f')
		return (0);
	return (1);
}

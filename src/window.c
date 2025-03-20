/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:43:22 by asezgin           #+#    #+#             */
/*   Updated: 2025/03/19 08:25:45 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/get_next_line.h"
#include <stdlib.h>
#include "../minilibx-linux/mlx.h"

int	close_window(t_fdf *fdf)
{
	get_next_line(-1);
	mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	mlx_destroy_display(fdf->mlx_ptr);
	free(fdf->mlx_ptr);
	free_map(fdf->map);
	free(fdf);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
		close_window(fdf);
	return (0);
}

void	setup_window(t_fdf *fdf)
{
	draw_map(fdf);
	mlx_key_hook(fdf->win_ptr, key_hook, fdf);
	mlx_hook(fdf->win_ptr, 17, 0, close_window, fdf);
	mlx_loop(fdf->mlx_ptr);
}

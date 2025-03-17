/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by user42            #+#    #+#             */
/*   Updated: 2025/03/17 09:55:41 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Pencereyi kapatır ve programı sonlandırır
*/
int	close_window(t_fdf *fdf)
{
	mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	free_map(fdf->map);
	free(fdf);
	exit(0);
	return (0);
}

/*
** Tuş basımlarını işler
*/
int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
		close_window(fdf);
	return (0);
}

/*
** Görüntüleme penceresini oluşturur ve olayları kaydeder
*/
void	setup_window(t_fdf *fdf)
{
	draw_map(fdf);
	mlx_key_hook(fdf->win_ptr, key_hook, fdf);
	mlx_hook(fdf->win_ptr, 17, 0, close_window, fdf);
	mlx_loop(fdf->mlx_ptr);
}

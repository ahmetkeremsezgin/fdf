/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:44:07 by asezgin           #+#    #+#             */
/*   Updated: 2025/03/20 15:09:27 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include "../minilibx-linux/mlx.h"

t_fdf	*init_fdf(t_map *map)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (!fdf)
		return (NULL);
	fdf->map = map;
	fdf->mlx_ptr = mlx_init();
	if (!fdf->mlx_ptr)
	{
		free(fdf);
		return (NULL);
	}
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FDF");
	if (!fdf->win_ptr)
	{
		free(fdf);
		return (NULL);
	}
	return (fdf);
}

static int	handle_error(char *msg, t_map *map)
{
	if (map)
		free_map(map);
	write(1, msg, ft_strlen(msg));
	return (1);
}

void	init_image(t_fdf *fdf)
{
	fdf->img.img_ptr = mlx_new_image(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	fdf->img.addr = mlx_get_data_addr
		(fdf->img.img_ptr, &fdf->img.bits_per_pixel,
			&fdf->img.line_length, &fdf->img.endian);
}

int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
	{
		exit_program(fdf);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf;
	t_map	*map;

	if (argc != 2)
		ft_error("Usage: ./fdf <filename.fdf>");
	if (!check_file_extension(argv[1]))
		ft_error("Error: File must have .fdf extension");
	map = read_map(argv[1]);
	if (!map)
		return (handle_error("Error: Map not found\n", NULL));
	fdf = init_fdf(map);
	if (!fdf)
		return (handle_error("Error: Failed to initialize FDF\n", map));
	get_next_line(-1);
	init_image(fdf);
	setup_window(fdf);
	mlx_key_hook(fdf->win_ptr, key_hook, fdf);
	mlx_hook(fdf->win_ptr, 17, 0, exit_program, fdf);
	return (0);
}

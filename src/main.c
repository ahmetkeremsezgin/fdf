/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:44:07 by asezgin           #+#    #+#             */
/*   Updated: 2025/03/19 08:38:27 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

int	main(int argc, char **argv)
{
	t_fdf	*fdf;
	t_map	*map;

	if (argc != 2)
		return (handle_error("Kullanım: ./fdf harita_dosyası.fdf\n", NULL));
	map = read_map(argv[1]);
	if (!map)
		return (handle_error("Harita okunamadı\n", NULL));
	fdf = init_fdf(map);
	if (!fdf)
		return (handle_error("FDF başlatılamadı\n", map));
	setup_window(fdf);
	return (0);
}

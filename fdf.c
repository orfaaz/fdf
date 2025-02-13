/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:33:50 by agamay            #+#    #+#             */
/*   Updated: 2025/01/28 17:17:32 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	to_iso(t_map *map)
{
	map->isomap = malloc(sizeof(t_isovtx *) * (map->lines + 1));
	if (!map->isomap)
		return ;
	map->isomap[map->lines] = NULL;
	while (map->map)
	{
		*(map->isomap) = projection_iso(*(map->map), map->trsfm);
		map->isomap++;
		map->map++;
	}
}

void	put_pxl(t_img *img, t_isovtx *vtx)
{
	char	*dst;

	dst = img->addr + (vtx->y * img->line_len + vtx->x * (img->bpp / 8));
	*(unsigned int *)dst = *(unsigned int *)vtx->color;
}

void	display(t_map *map)
{
	t_win	win;
	t_img	img;

	win.mlx = mlx_init();
	win.win = mlx_new_window(win.mlx, WIDTH, HEIGHT, "fdf");
	img.img = mlx_new_image(win.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, 
								&img.line_len, &img.endian);
	while (map->isomap)
	{
		put_pxl(&img, *(map->isomap));
		map->isomap++;
	}
	mlx_put_image_to_window(win.mlx, win.win, img.img, 0, 0);
	mlx_loop(win.mlx);
	//draw vertices;
	//drawlines;
	//push img;
}

int	main(int ac, char **av)
{
	int		fd;
	t_map	*map;

	if (ac != 2 || !ft_strnstr(av[1], ".fdf", ft_strlen(av[1])))
		exit(EXIT_FAILURE);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		exit(EXIT_FAILURE);
	map = parser(fd);
	to_iso(map);
	display(map);
	free(map);
}

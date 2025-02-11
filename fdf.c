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

void	display(char *map)
{
	t_win	*win;
	t_img	*img;

	win->mlx = mlx_init();
	img->img = mlx_new_image(win->mlx, 1920, 1080);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, 
								&img->line_len, &img->endian);
	
}

void	put_pxl(t_img *img, t_isovtx vtx)
{
	char	*dst;

	dst = img->addr + (vtx->y * img->line_len + vtx->x * (img->bpp / 8));
	*(unsigned int *)dst = vtx->color;
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
	display(map);
}

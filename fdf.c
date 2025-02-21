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
	int	i;

	i = -1;
	map->isomap = malloc(sizeof(t_isovtx *) * (map->vtc_nb + 1));
	if (!map->isomap)
		return ;
	map->isomap[map->vtc_nb] = NULL;
	while (++i < map->vtc_nb)
	{
		map->isomap[i] = projection_iso(map->map[i], map->trsfm);
	}
}

void	put_pxl(t_img *img, t_isovtx *vtx, unsigned int color)
{
	char	*dst;

	if (vtx->y >= 0 && vtx->y <= HEIGHT && vtx->x >= 0 && vtx->x <= WIDTH)
	{
		dst = img->addr + (ft_round(vtx->y) * img->line_len + ft_round(vtx->x) * (img->bpp / 8));
		//*(unsigned int *)dst = *(unsigned int *)vtx->color;
		*(unsigned int *)dst = color;
	}
}
void	screen_reset(t_img *img)
{
	t_isovtx	black;
	int			i;

	i = -1;
	black.y = 1;
	while (++i < HEIGHT * WIDTH - 1)
	{
		black.x = i;
		put_pxl(img, &black, 0);
	}
}

//blacks out screen, draw vertices, then edges, then pushes image;
void	display(t_map *map, t_win *win)
{
	t_img		*img;
	int			i;

	img = win->img;
	screen_reset(img);
	i = -1;
	while (++i < map->vtc_nb)
	{
		put_pxl(img, map->isomap[i], 0xA2D8A0);//vert 0xA2D8A0
	}
	i = -1;
	while (++i < map->vtc_nb)
	{
		if (i % map->line_len)
			drawline(*(map->isomap[i]), *(map->isomap[i - 1]), img);
		if (i >= map->line_len)
			drawline(*(map->isomap[i]), *(map->isomap[i - map->line_len]), img);
	}
	mlx_put_image_to_window(win->mlx, win->win, img->img, 0, 0);
}

t_win	*set_win(void)
{
	t_win	*win;
	t_img	*img;

	win = malloc(sizeof(t_win));
	img = malloc(sizeof(t_img));
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, WIDTH, HEIGHT, "fdf");
	img->img = mlx_new_image(win->mlx, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, 
								&img->line_len, &img->endian);
	win->img = img;
	return (win);
}

int	main(int ac, char **av)
{
	int		fd;
	t_win	*win;
	t_map	*map;

	if (ac != 2 || !ft_strnstr(av[1], ".fdf", ft_strlen(av[1])))
		exit(EXIT_FAILURE);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		exit(EXIT_FAILURE);
	map = parser(fd);
	to_iso(map);
	win = set_win();
	win->trsfm = map->trsfm;
	display(map, win);
	mlx_loop_hook(win->mlx, &no_event, win);
	mlx_key_hook(win->win, &hook_parser, win);
	mlx_loop(win->mlx);
	free(map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:33:50 by agamay            #+#    #+#             */
/*   Updated: 2025/02/23 14:56:46 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//blacks out screen, draw vertices, then edges, then pushes image;
void	display(t_map *map, t_win *win)
{
	t_img		*img;
	int			i;

	to_iso(map);
	img = win->img;
	screen_reset(img);
	i = -1;
	while (++i < map->vtc_nb)
	{
		put_pxl(img, map->isomap[i], 0xDD9090);
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

//sets up everything the mlx needs.
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

//unsets mlx and frees everything.
void	end(t_win *win, t_map *map)
{
	t_img	*img;

	img = win->img;
	mlx_destroy_image(win->mlx, img->img);
	free(img);
	mlx_destroy_window(win->mlx, win->win);
	mlx_destroy_display(win->mlx);
	free(win->mlx);
	free(win);
	dbarr_free((void **)map->map);
	dbarr_free((void **)map->isomap);
	free(map->trsfm);
	free(map);
}

int	main(int ac, char **av)
{
	int		fd;
	t_win	*win;
	t_map	*map;

	if (ac != 2 || !ft_strnstr(av[1], ".fdf", ft_strlen(av[1])))
	{
		ft_putstr_fd("expected argument: one .fdf file", 2);
		exit(EXIT_FAILURE);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		perror("opening map failed");
		exit(EXIT_FAILURE);
	}
	map = parser(fd);
	close(fd);
	win = set_win();
	win->trsfm = map->trsfm;
	win->map = map;
	display(map, win);
	mlx_hook(win->win, 17, 0, close_win, win);
	mlx_key_hook(win->win, &hook_parser, win);
	mlx_loop(win->mlx);
	end(win, map);
}

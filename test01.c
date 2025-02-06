#include "fdf.h"

typedef	struct	s_img
{
	void	*img;
	char	*addr;
	int		line_len;
	int		bpp;
	int		endian;
}				t_img;

typedef	struct	s_win
{
	void	*mlx;
	void	*win;
}				t_win;

void	put_pxl(t_img *img, int u, int v, int color)
{
	char	*dst;

	dst = img->addr + (v * img->line_len + u * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	main(void)
{
	t_win	win;
	t_img	img;
	t_map	*map;
	int mfd = open("./maps/test_maps/basictest.fdf", O_RDONLY);
	map = parser(mfd);
	close(mfd);
	
	// int i = 0;
	// int j = 0;
	// while (map->map[i])
	// {
	// 	while(map->map[i][j])
	// 	{
	// 		ft_printf("%c, ", map->map[i][j]);
	// 		j++;
	// 	}
	// 	j = 0;
	// 	i++;
	// }

	win.mlx = mlx_init();
	win.win = mlx_new_window(win.mlx, 500, 500, "fdf_test");
	
	img.img = mlx_new_image(win.mlx, 500, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	put_pxl(&img, 5, 5, 0x0FF0000);
	//put a pixel for each value in map.
	mlx_put_image_to_window(win.mlx, win.win, img.img, 0, 0);
	mlx_loop(win.mlx);
}
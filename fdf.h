/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:34:06 by agamay            #+#    #+#             */
/*   Updated: 2025/02/23 14:57:09 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <libft.h>
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef WIDTH
#  define WIDTH 800
# endif
# ifndef HEIGHT
#  define HEIGHT 600
# endif

//Coordinates structs.
typedef struct s_vtx
{
	int		x;
	int		y;
	int		z;
}				t_vtx;

typedef struct s_isovtx
{
	float		x;
	float		y;
}				t_isovtx;

typedef struct s_isovector
{
	t_isovtx	*a;
	t_isovtx	*b;
	float		xinc;
	float		yinc;
	float		dx;
	float		dy;
}				t_isovector;

typedef struct s_transform
{
	int	tx;
	int	ty;
	int	scale;
	int	prev;
}				t_transform;

typedef struct s_map
{
	t_vtx		**map;
	t_isovtx	**isomap;
	t_transform	*trsfm;
	int			line_len;
	int			lines;
	int			vtc_nb;
}				t_map;

//Mlx structs.
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		line_len;
	int		bpp;
	int		endian;
}				t_img;

typedef struct s_win
{
	void		*mlx;
	void		*win;
	t_img		*img;
	t_map		*map;
	t_transform	*trsfm;
}				t_win;

t_map		*parser(int fd);
void		to_iso(t_map *map);
void		display(t_map *map, t_win *win);
void		put_pxl(t_img *img, t_isovtx *vtx, unsigned int color);
void		drawline(t_isovtx a, t_isovtx b, t_img *img);
void		screen_reset(t_img *img);
int			no_event(void *data);
int			hook_parser(int keysym, void *data);
void		dbarr_free(void **arr);
float		ft_abs(float n);
int			ft_round(float n);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:34:06 by agamay            #+#    #+#             */
/*   Updated: 2025/01/28 16:34:07 by agamay           ###   ########.fr       */
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
# include <stdio.h> //perror
# include <string.h> //strerror
# include <fcntl.h>

# ifndef WIDTH
#  define WIDTH 600
# endif
# ifndef HEIGHT
#  define HEIGHT 400
# endif

//Coordinates structs.
typedef struct	s_vtx
{
	int		x;
	int		y;
	int		z;
	char	*color;//unused
}				t_vtx;

typedef struct	s_isovtx
{
	float		x;
	float		y;
	char	*color;//unused
}				t_isovtx;

typedef struct	s_isovector
{
	t_isovtx	*a;
	t_isovtx	*b;
	float		xinc;
	float		yinc;
	float		dx;
	float		dy;
}				t_isovector;

typedef struct	s_transform
{
	int	tx;
	int	ty;
	int	scale;
	//int	z_scale;
}				t_transform;

typedef struct	s_map
{
	t_vtx		**map;
	t_isovtx	**isomap;
	t_transform	*trsfm;
	int			line_len;
	int			lines;
	int			vtc_nb;
}				t_map;

//Mlx structs.
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
	void		*mlx;
	void		*win;
	t_img		*img;
	t_transform	*trsfm;
}				t_win;

t_map		*parser(int fd);
t_isovtx	*projection_iso(t_vtx *vtx, t_transform *trsfm);
t_transform	*set_transform(void);
void		drawline(t_isovtx a, t_isovtx b, t_img *img);
void		put_pxl(t_img *img, t_isovtx *vtx, unsigned int color);
int			no_event(void *data);
int			hook_parser(int keysym, void *data);
float		ft_abs(float n);
int			ft_round(float n);
int			ft_countwords(char *str, char stop);
void		free_map(t_map *map);
#endif
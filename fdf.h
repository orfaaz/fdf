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

typedef struct s_cmap
{
	char	**map;
	int		line_len;
	int		lines;
}				t_cmap;

typedef struct	s_point
{
	float	x;
	float	y;
	float	z;
}				t_point;


typedef struct	s_rotate
{
	int	rx;
	int	ry;
	int	rz;
}				t_rotate;

typedef struct	s_translate
{
	int	tx;
	int	ty;
	int	tz;
}				t_translate;

/* 3D orga

w = 1920 h = 1080;
aspect ratio = a = h / w
foc = ?;

chaque vtx : [x, y, z];
chaque triangle : [vtx01, vtx02, vtx03];
chaque face : triangle01, triangle02; (faces pas forcement necessaire pour l'instant)
mesh : enssemble des faces

projection
float	ft_fov(int foc)
{
	float	ret;

	ret = 1 / (tan (fov / 2));
	return (ret);
}

float	ft_q(int fclip, int nclip)
{
	float	ret;

	ret = (fclip / (fclip - nclip);
	return (ret);
}

coordinates projection formula:
[afx / z, fy / z, zq - nclip q];
(/z pour la persp?)
matrice de projection: mult coord [x, y, z, 1] par
[af, 0, 0,   0];
[0 , f, 0,   0];
[0 , 0, q,   1];
[0 , 0,-ncq, 0];

 = [afx / z, fy / z, zq - nclip q, z];
 
*/

t_map	*parser(int fd);
#endif
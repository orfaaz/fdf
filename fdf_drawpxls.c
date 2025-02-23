/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_drawpxls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:43:35 by agamay            #+#    #+#             */
/*   Updated: 2025/02/23 14:56:56 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pxl(t_img *img, t_isovtx *vtx, unsigned int color)
{
	char	*dst;

	if (vtx->y >= 0 && vtx->y < HEIGHT
		&& vtx->x >= 0 && ft_round(vtx->x) < WIDTH)
	{
		dst = img->addr + (ft_round(vtx->y) * img->line_len
				+ ft_round(vtx->x) * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

//draws a straight line between 2D vtc a and b.
void	drawline(t_isovtx a, t_isovtx b, t_img *img)
{
	t_isovector	v;
	int			i;

	v.a = &a;
	v.b = &b;
	v.dx = b.x - a.x;
	v.dy = b.y - a.y;
	if (ft_abs(v.dx) > ft_abs(v.dy))
	{
		v.xinc = v.dx / ft_abs(v.dx);
		v.yinc = v.dy / ft_abs(v.dx);
	}
	else
	{
		v.xinc = v.dx / ft_abs(v.dy);
		v.yinc = v.dy / ft_abs(v.dy);
	}
	i = 0;
	while (i < ft_abs(v.dx) || i < ft_abs(v.dy))
	{
		v.a->x = v.a->x + v.xinc;
		v.a->y = v.a->y + v.yinc;
		put_pxl(img, v.a, 0xA2D8A0);
		i++;
	}
}

//blacks out screen before drawing on it again.
void	screen_reset(t_img *img)
{
	t_isovtx	black;
	int			i;

	i = -1;
	black.y = -1;
	black.x = -1;
	while (++i < HEIGHT * WIDTH)
	{
		black.x++;
		if (i % WIDTH == 0)
		{
			black.y++;
			black.x = 0;
		}
		put_pxl(img, &black, 0);
	}
}

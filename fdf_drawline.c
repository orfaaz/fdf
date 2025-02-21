/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_drawline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:43:35 by agamay            #+#    #+#             */
/*   Updated: 2025/02/13 11:43:37 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"


//prepares values to draw the .
void	drawline(t_isovtx a, t_isovtx b, t_img *img)
{
	t_isovector	v;
	int	i;
	
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
		put_pxl(img, v.a, 0xFFFFFF);
		i++;
	}
}

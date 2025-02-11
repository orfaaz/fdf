
#include "fdf.h"

//draws pixls on a vertical line. stepping one pixel aside when needed.
void	steep_slope(t_isovector v, t_img img)
{
	int	i;
	int	step;

	i = -1;
	step = 2 * ft_abs(v.dx) - ft_abs(v.dy);
	while (++i < ft_abs(v.dy))
	{
		if (v.dy > 0)
			v.a.y++;
		else
			v.a.y--;
		if (step < 0)
			step = step + 2 * v.dy;
		else
		{
			if (v.dx > 0)
				v.a.x++;
			else
				v.a.x--;
			step = step + 2 * v.dx - 2 * v.dy;
		}
		put_pxl(img, v.a.x, v.a.y, 0xA2D8A0);
	}
}

//draws pixls on a horizontal line. stepping one pixel up when needed.
void	gentle_slope(t_isovector v, t_img img)
{
	int	i;
	int	up;

	i = -1;
	up = 2 * ft_abs(v.dy) - ft_abs(v.dx);
	while (++i < ft_abs(v.dx))
	{
		if (v.dx > 0)
			v.a.x++;
		else
			v.a.x--;
		if (up < 0)
			up = up + 2 * v.dy;
		else
		{
			if (v.dy > 0)
				v.a.y++;
			else
				v.a.y--;
			up = up + 2 * v.dy - 2 * v.dx;
		}
		put_pxl(img, v.a.x, v.a.y, 0xA2D8A0);
	}
}

//checks the slope of the vector ab(dx, dy) to draw it right.
void	drawslope_parse(t_isovtx a, t_isovtx b, t_img img)
{
	t_isovector	v;
	
	v.a = a;
	v.b = b;
	v.dx = b.x - a.x;
	v.dy = b.y - a.y;
	if (ft_abs(dx) > ft_abs(dy))
		gentle_slope(v, img);
	else
		steep_slope(v, img);
}


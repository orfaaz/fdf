/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:42:39 by agamay            #+#    #+#             */
/*   Updated: 2025/02/23 14:57:21 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	no_event(void *data)
{
	(void)data;
	return (0);
}

//unsets mlx window, breaking out of the mlx loop.
int	close_win(t_win *win)
{
	// t_img	*img;

	// img = win->img;
	// mlx_destroy_image(win->mlx, img->img);
	// free(img);
	// mlx_destroy_window(win->mlx, win->win);
	mlx_loop_end(win->mlx);
	return (0);
}

//modifies t_transforms values according to the input.
void	transform(t_win *win, char c)
{
	t_map		*map;
	t_transform	*trsfm;

	map = win->map;
	trsfm = win->trsfm;
	if (c == 'l')
		trsfm->tx -= 3;
	else if (c == 'r')
		trsfm->tx += 3;
	else if (c == 'u')
		trsfm->ty -= 3;
	else if (c == 'd')
		trsfm->ty += 3;
	else if (c == '+' && trsfm->scale < 1000)
		trsfm->scale++;
	else if (c == '-' && trsfm->scale > 1)
		trsfm->scale--;
	display(map, win);
}

//checks inputs, and rederects to the according functions.
int	hook_parser(int keysym, void *data)
{
	t_win		*win;
	t_transform	*trsfm;

	win = (t_win *)data;
	trsfm = win->trsfm;
	if (keysym == XK_Escape)
		close_win(win);
	else if (keysym == XK_Left)
		transform(win, 'l');
	else if (keysym == XK_Right)
		transform(win, 'r');
	else if (keysym == XK_Up)
		transform(win, 'u');
	else if (keysym == XK_Down)
		transform(win, 'd');
	else if (keysym == XK_Shift_R)
		transform(win, '+');
	else if (keysym == XK_Control_R)
		transform(win, '-');
	return (0);
}

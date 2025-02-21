/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:42:39 by agamay            #+#    #+#             */
/*   Updated: 2025/02/21 17:42:45 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_win(t_win *win)
{
	t_img	*img;

	img = win->img;
	// mlx_destroy_img();
	free(img);
	mlx_destroy_window(win->mlx, win->win);
	mlx_destroy_display(win->mlx);
	free(win->mlx);
	free(win);
	return (0);
}

int	no_event(void *data)
{
	(void)data;
	return (0);
}

int	hook_parser(int keysym, void *data)//!\code copié, à modifier
{
	t_win		*win;
	t_transform	*trsfm;

	win = (t_win *)data;
	trsfm = win->trsfm;
	if (keysym == XK_Escape)
		close_win(win);
	return (0);
}

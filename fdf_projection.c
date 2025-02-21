/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_projection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:43:48 by agamay            #+#    #+#             */
/*   Updated: 2025/02/13 11:43:50 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_isovtx	*projection_iso(t_vtx *vtx, t_transform *trsfm)
{
	t_isovtx *iso;

	iso = malloc(sizeof(t_isovtx));
	if (!iso)
		return (NULL);
	iso->x = ((float)vtx->x - (float)vtx->y) * cos(0.523599);
	iso->x = iso->x + (float)trsfm->tx;
	iso->y = ((float)vtx->x + (float)vtx->y) * sin(0.523599) - (float)vtx->z;
	iso->y = iso->y + (float)trsfm->ty;
	iso->color = vtx->color;
	return (iso);
}

t_transform	*set_transform(void)
{
	t_transform	*trsfm;

	trsfm = malloc(sizeof(t_transform));
	trsfm->scale = 10; //arbitrary value
	trsfm->tx = WIDTH / 2;
	trsfm->ty = HEIGHT / 2;
	return (trsfm);
}

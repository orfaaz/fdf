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

static t_isovtx	*projection_iso(t_vtx *vtx, t_transform *trsfm)
{
	t_isovtx	*iso;

	iso = malloc(sizeof(t_isovtx));
	if (!iso)
		return (NULL);
	iso->x = ((float)vtx->x - (float)vtx->y) * cos(0.523599);
	iso->x = iso->x + (float)trsfm->tx;
	iso->y = ((float)vtx->x + (float)vtx->y) * sin(0.523599) - (float)vtx->z;
	iso->y = iso->y + (float)trsfm->ty;
	return (iso);
}

static void	scale_map(t_map *map)
{
	t_vtx		*vtx;
	t_transform	*trsfm;
	int			i;

	trsfm = map->trsfm;
	i = -1;
	while (++i < map->vtc_nb)
	{
		vtx = map->map[i];
		vtx->x = vtx->x / trsfm->prev * trsfm->scale;
		vtx->y = vtx->y / trsfm->prev * trsfm->scale;
		vtx->z = vtx->z / trsfm->prev * trsfm->scale;
	}
	trsfm->prev = trsfm->scale;
}

//converts 3D map to 2D isometric projection 
//by rotating and projecting each 3D vtx individually.
void	to_iso(t_map *map)
{
	int	i;

	i = -1;
	if (map->isomap)
		dbarr_free((void **)map->isomap);
	map->isomap = malloc(sizeof(t_isovtx *) * (map->vtc_nb + 1));
	if (!map->isomap)
		return ;
	map->isomap[map->vtc_nb] = NULL;
	scale_map(map);
	while (++i < map->vtc_nb)
		map->isomap[i] = projection_iso(map->map[i], map->trsfm);
}

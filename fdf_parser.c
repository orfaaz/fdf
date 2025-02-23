/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:33:59 by agamay            #+#    #+#             */
/*   Updated: 2025/01/28 17:23:40 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_transform	*set_transform(void)
{
	t_transform	*trsfm;

	trsfm = malloc(sizeof(t_transform));
	trsfm->scale = 10;
	trsfm->prev = 10;
	trsfm->tx = WIDTH / 2;
	trsfm->ty = HEIGHT / 2;
	return (trsfm);
}

int	is_map_rectangle(t_map *map, char *strmap, int fd)
{
	char	*tmp;
	int		line_len;
	int		i;

	i = 0;
	tmp = strmap;
	line_len = ft_countwords(strmap, '\n');
	while (++i < map->lines)
	{
		while (*tmp != '\n')
			tmp++;
		if (line_len != ft_countwords(++tmp, '\n'))
		{
			free(map->trsfm);
			free(map);
			free(strmap);
			close(fd);
			ft_putstr_fd("map must be rectangle", 2);
			exit (EXIT_FAILURE);
		}
	}
	return (line_len);
}

//assign the right coordinate to the t_vtx struct.
static void	assign_coordinates(t_map *map, char *strmap, int crdnts[2])
{
	t_vtx		*vtx;
	t_transform	*scale;
	int			i;

	scale = map->trsfm;
	i = crdnts[0] + crdnts[1] * map->line_len;
	vtx = malloc(sizeof(t_vtx));
	if (!vtx)
		return ;
	map->map[i] = vtx;
	vtx->x = crdnts[0] * scale->scale;
	vtx->y = crdnts[1] * scale->scale;
	vtx->z = ft_atoi(strmap) * scale->scale;
	while (*strmap && !(*strmap == ' ' && *strmap == ','))
		strmap++;
}

//converts the char* map from gnl to an array of structs 
//containing (x, y, z) informations. (colors are ignored).
static void	char_to_vtx(t_map *map, char *strmap)
{
	int	crdnts[2];

	crdnts[0] = 0;
	crdnts[1] = 0;
	map->map = malloc(sizeof(t_vtx *) * (map->vtc_nb + 1));
	if (!map->map)
		return ;
	map->map[map->vtc_nb] = NULL;
	while (crdnts[0] < map->line_len || crdnts[1] < map->lines - 1)
	{
		if (*strmap == '\n')
		{
			crdnts[0] = 0;
			crdnts[1]++;
			strmap++;
		}
		assign_coordinates(map, strmap, crdnts);
		crdnts[0]++;
		while (*strmap && (*strmap != ' ' && *strmap != '\n'))
			strmap++;
		while (*strmap && *strmap == ' ')
			strmap++;
	}
}

//Reads .fdf doc. Creates a struct containing a **struct_vtx of coordinates
//counts w and l of map.
t_map	*parser(int fd)
{
	t_map	*map;
	char	*tmp;
	char	*join;

	map = malloc(sizeof(t_map));
	if (!map)
		exit(EXIT_FAILURE);
	map->trsfm = set_transform();
	map->map = NULL;
	map->isomap = NULL;
	map->lines = 0;
	join = NULL;
	tmp = get_next_line(fd);
	while (tmp)
	{
		join = ft_strjoin_free(join, tmp);
		free(tmp);
		tmp = get_next_line(fd);
		map->lines++;
	}
	map->line_len = is_map_rectangle(map, join, fd);
	map->vtc_nb = map->lines * map->line_len;
	char_to_vtx(map, join);
	free(join);
	return (map);
}

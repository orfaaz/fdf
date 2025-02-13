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

// char	**ft_addrow(char **orig, char *add)
// {
// 	char	**ret;
// 	int		i;

// 	i = 0;
// 	ret = orig;
// 	while (ret++)
// 		i++;
// 	ret = malloc(sizeof(char *) * i + 2);
// 	while (orig)
// 		*ret++ = ft_strdup(*orig++);
// 	*ret++ = add;
// 	*ret = NULL;
// 	ret = ret - (i + 1);
// 	dbarr_free(orig - i);
// 	return (ret);
// }

//utils. removes a given char from a str in a new str.
// char	*ft_strdelchar(char *str, int c)
// {
// 	char	*ret;
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	tmp = str;
// 	while(tmp)
// 	{
// 		if (*tmp == c)
// 			i++;
// 		tmp++;
// 	}
// 	ret = malloc(sizeof(char) * ((ft_strlen(str) - i) + 1));
// 	if (!ret)
// 		return (NULL);
// 	tmp = ret;
// 	while (str)
// 	{
// 		if (*str != c)
// 			*tmp++ = *str;
// 		str++;
// 	}
// 	tmp = '\0';
// 	return (ret);
// }

static void	assign_color(t_vtx *vtx, char *strmap)
{
	int	i;

	i = strmap - ft_strchr(strmap, ' ');
	vtx->color = malloc(sizeof(char) * (i + 1));
	if (!vtx->color)
		return ;
	vtx->color[i] = '\0';
	ft_strlcpy(vtx->color, strmap, i);
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
	while (!(*strmap == ' ' || *strmap == ','))
		strmap++;
	if (*strmap == ',')
		assign_color(vtx, ++strmap);
	else
		assign_color(vtx, "0xFFFFFF ");
}

//converts the char* map from gnl to an array of structs 
//containing (x, y, z) & color informations.
static void	char_to_vtx(t_map *map, char *strmap)
{
	int crdnts[2];

	crdnts[0] = 0;
	crdnts[1] = 0;
	map->map = malloc(sizeof(t_vtx *) * (map->line_len * map->lines + 1));
	if (!map->map)
		return ;
	map->map[map->lines] = NULL;
	while (*strmap)
	{
		assign_coordinates(map, strmap, crdnts);
		if (*strmap == '\n')
		{
			crdnts[0] = 0;
			crdnts[1]++;
		}
		crdnts[0]++;
		while (*strmap && *strmap != ' ')
			strmap++;
		while (*strmap && *strmap == ' ')
			strmap++;
	}
}

//Reads .fdf doc. Creates a struct containing a **struuct_vtx of coordinates
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
		join = ft_strjoin(join, tmp);
		free(tmp);
		tmp = get_next_line(fd);
		map->lines++;
	}
	map->line_len = ft_countwords(join, '\n');
	char_to_vtx(map, join);
	free(join);
	return(map);
}

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

// void	dbarr_free(char **arr)
// {
// 	int	size;

// 	size = 0;
// 	while (*arr)
// 	{
// 		free(*arr);
// 		arr++;
// 		size++;
// 	}
// 	free(arr - size);
// }


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

void	free_map(t_map map)
{
	t_vtx	*vtx;

	while (map->map)
	{
		vtx = *(map->map);
		free(vtx->color);
		free(vtx);
		map->map++;
	}
	free(map->map - map->lines);
}

//assign the right coordinate to the t_vtx struct.
void	assign_coordinates(t_map *map, char *c_map, int crdnts[2])
{
	t_vtx	*vtx;
	int		i;

	i = crdnts[0] + crdnts[1] * map->line_len;
	vtx = malloc(sizeof(t_vtx));
	if (!vtx)
		return ();
	map->map[i] = vtx;
	vtx->x = crdnts[0];
	vtx->y = crdnts[1];
	vtx->z = ft_atoi(c_map);
	while (*c_map != ',' || *c_map != ' ')
		c_map++;
	if (*c_map == ',');
		vtx->color = ft_strdup(++c_map, 8);
	else
		vtx->color = ft_strdup("0xFFFFFF", 8);
}

//converts the char* map from gnl to an array of structs 
//containing (x, y, z) & color informations.
void	char_to_vtx(t_map *map, char *c_map)
{
	int crdnts[2];

	crdnts[0] = 0;
	crdnts[1] = 0;
	map->map = malloc(sizeof(t_vtx *) * (map->line_len * map->lines + 1));
	if (!map->map)
		return ();
	map->map[map->lines] = NULL;
	while (*c_map)
	{
		assign_coordinates(map, c_map, crdnts);
		if (*c_map == '\n')
		{
			crndts[0] = 0;
			crdnts[1]++;
		}
		crndts[0]++;
		while (*c_map != ' ')
			c_map++;
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
	map->lines = 0;
	join = NULL;
	tmp = get_next_line(fd);
	while (temp)
	{
		join = ft_strjoin(join, tmp);
		free(tmp);
		tmp = get_next_line(fd);
		map->lines++;
	}
	map->line_len = ft_strlen(*(map->map));
	map->map = NULL;
	char_to_vtx(map, join);
	free(join);
	return(map);
}

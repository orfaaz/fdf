/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_3D_projection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:43:23 by agamay            #+#    #+#             */
/*   Updated: 2025/02/13 11:43:30 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//computes pield of view depending on cam angle. 
//gives the scaling factor?
float	ft_fov(int foc)
{
	float	ret;

	ret = 1 / (tan (fov / 2));
	return (ret);
}

//scaling foctor for the z axis. 
float	ft_q(int fclip, int nclip)
{
	float	ret;

	ret = (fclip / (fclip - nclip));
	return (ret);
}

/* 3D orga

w = 1920 h = 1080;
aspect ratio = a = h / w
foc = ?;

chaque vtx : [x, y, z];
chaque triangle : [vtx01, vtx02, vtx03];
chaque face : triangle01, triangle02; (faces pas forcement necessaire pour l'instant)
mesh : enssemble des faces

projection
float	ft_fov(int foc)
{
	float	ret;

	ret = 1 / (tan (fov / 2));
	return (ret);
}

float	ft_q(int fclip, int nclip)
{
	float	ret;

	ret = (fclip / (fclip - nclip);
	return (ret);
}

coordinates projection formula:
[afx / z, fy / z, zq - nclip q];
(/z pour la persp?)
matrice de projection: mult coord [x, y, z, 1] par
[af, 0, 0,   0];
[0 , f, 0,   0];
[0 , 0, q,   1];
[0 , 0,-ncq, 0];

 = [afx / z, fy / z, zq - nclip q, z];
 
*/

//abandonned fct


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

//color managment

// static void	assign_color(t_vtx *vtx, char *strmap)
// {
// 	int	i;

// 	i = strmap - ft_strchr(strmap, ' ');//probleme si la couleur est suivie d'un '\n';
// 	vtx->color = malloc(sizeof(char) * (i + 1));
// 	if (!vtx->color)
// 		return ;
// 	vtx->color[i] = '\0';
// 	ft_strlcpy(vtx->color, strmap, i);
// }

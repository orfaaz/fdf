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
char	*ft_strdelchar(char *str, int c)
{
	char	*ret;
	char	*tmp;
	int		i;

	i = 0;
	tmp = str;
	while(tmp)
	{
		if (*tmp == c)
			i++;
		tmp++;
	}
	ret = malloc(sizeof(char) * ((ft_strlen(str) - i) + 1));
	if (!ret)
		return (NULL);
	tmp = ret;
	while (str)
	{
		if (*str != c)
			*tmp++ = *str;
		str++;
	}
	tmp = '\0';
	return (ret);
}
//reads .fdf document. place its content in a **char and counts w and l of map.
t_cmap	*parser(int fd)
{
	t_cmap	*cmap;
	char	*temp;
	char	*join;

	cmap = malloc(sizeof(t_cmap));
	if (!cmap)
		exit(EXIT_FAILURE);
	cmap->lines = 0;
	join = NULL;
	temp = get_next_line(fd);
	while (temp)
	{
		join = ft_strjoin(join, temp);
		free(temp);
		temp = get_next_line(fd);
		cmap->lines++;
	}
	temp = join;
	join = ft_strdelchar(join, ' ');
	free(temp);
	cmap->map = ft_split(join, '\n');//should map be char* or int*?
	free(join);
	cmap->line_len = ft_strlen(*(cmap->map));
	return(cmap);
}


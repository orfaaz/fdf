/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:43:56 by agamay            #+#    #+#             */
/*   Updated: 2025/02/13 11:43:58 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	ft_abs(float n)
{
	if (n < 0)
		n = -n;
	return (n);
}

int	ft_round(float n)
{
	if ((int)n == (int)(n + 0.5))
		return ((int)n);
	return ((int)n + 1);
}

static int	ft_isspace3(const char c)
{
	if ((c >= 9 && c <= 13) || (c == ' '))
		return (1);
	return (0);
}

void	dbarr_free(void **arr)
{
	int	size;

	size = 0;
	while (*arr)
	{
		free(*arr);
		arr++;
		size++;
	}
	free(arr - size);
}

void	free_map(t_map *map)
{
	if (map->map)
		dbarr_free((void *)map->map);
	if (map->isomap)
		dbarr_free((void *)map->isomap);
	if (map->trsfm)
		free(map->trsfm);
	free(map);
}

int	ft_countwords(char *str, char stop)
{
	int	count;

	count = 0;
	if (!str || !*str || *str == stop)
		return (count);
	while (ft_isspace3(*str))
	{
		str++;
		if (*str == stop)
			return (count);
	}
	while (*str != stop)
	{
		if (ft_isspace3(*str) && ft_isalnum(*(str + 1)))
			count++;
		str++;
	}
	return (count + 1);
}

// int	ft_atoi_base(const char *nbr, int base)
// {
// 	int	sign;
// 	int	num;

// 	sign = 0;
// 	num = 0;
// 	while (ft_isspace3(*nbr))
// 		nbr++;
// 	if (*nbr == '-')
// 	{
// 		sign = 1;
// 		nbr++;
// 	}
// 	else if (*nbr == '+')
// 		nbr++;
// 	while ((*nbr >= '0' && *nbr <= '9') 
// 		|| (*nbr >= 'A' && *nbr <= 'A' + base))
// 	{
// 		num = num * base + (*nbr - 48);
// 		nbr++;
// 	}
// 	if (sign == 1)
// 		return (-num);
// 	return (num);
// 	0x0000FF
// }

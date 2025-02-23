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

inline float	ft_abs(float n)
{
	if (n < 0)
		n = -n;
	return (n);
}

int	ft_round(float n)
{
	if ((int)n == (int)(n + 0.5))
		return ((int)n);
	return ((int)(n + 0.5));
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

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


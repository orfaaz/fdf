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
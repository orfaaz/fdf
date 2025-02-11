
#include "fdf.h"

t_isovtx	projection_iso(t_vtx vtx, t_transform trsfm)
{
	t_isovtx iso;

	iso.x = (vtx.x - vtx.y) * cos(0.523599);
	iso.x = iso.x + trsfm.tx;
	iso.y = (vtx.x + vtx.y) * sin(0.523599) - vtx.z;
	iso.y = iso.y + trsfm.ty;
	// iso.color = vtx.color;
	return (iso);
}
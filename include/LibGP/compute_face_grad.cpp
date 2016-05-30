#include "compute_face_grad.h"

namespace LibGP
{
	LIBGP_INLINE void compute_face_grad(
		Matrix3f& grad, Float* pv0, Float* pv1, Float* pv2)
	{
		Vector3f e0(pv2[0] - pv1[0], pv2[1] - pv1[1], pv2[2] - pv1[1]);
		Vector3f e1(pv0[0] - pv2[0], pv0[1] - pv2[1], pv0[2] - pv2[1]);
		Vector3f e2(pv1[0] - pv0[0], pv1[1] - pv0[1], pv1[2] - pv0[1]);
		Vector3f n = e0.cross(e1);

		Float d = n.squaredNorm();
		if (d < EPS) d = EPS;
		
		grad.col(0) = n.cross(e0) / d;
		grad.col(1) = n.cross(e1) / d;
		grad.col(2) = n.cross(e2) / d;
	}
}

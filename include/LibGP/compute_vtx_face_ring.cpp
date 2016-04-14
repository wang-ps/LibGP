#include "compute_vtx_face_ring.h"

namespace LibGP
{
	LIBGP_INLINE void compute_vtx_face_ring(
		vecveci& vec, const MatrixXi& F)
	{
		vec.resize(F.maxCoeff() + 1);
		for (int i = 0; i < F.cols(); i++)
		{
			for (int j = 0; j < 3; j++)
			{
				vec[F(j, i)].push_back(i);
			}
		}
	}
}

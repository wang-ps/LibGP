#include "compute_vtx_face_ring.h"

LIBGP_INLINE void LibGP::compute_vtx_face_ring(
	std::vector<std::vector<int>>& vec, 
	const Eigen::MatrixXi& F)
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



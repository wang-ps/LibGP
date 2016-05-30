#include "compute_mesh_laplacian.h"

namespace LibGP
{
	LIBGP_INLINE void compute_mesh_laplacian(SMatrixf& L,
		const MatrixXf& V, const MatrixXi& F,
		bool uniform = false, bool normalize = false)
	{
		int nf = F.cols();
		int nv = V.cols();

		VectorXf weight = VectorXf::Ones(3 * nf);
		#pragma omp parallel for
		for (int i = 0; i < nf; i++)
		{
			Vector3f p0 = V.col(F(0, i));
			Vector3f p1 = V.col(F(1, i));
			Vector3f p2 = V.col(F(2, i));

			Float sinA = (p0 - p1).cross(p0 - p2).norm();

			for (int j = 0; j < 3; j++)
			{

			}
		}
	}
}




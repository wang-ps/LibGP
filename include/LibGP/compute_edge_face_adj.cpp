#include "compute_edge_face_adj.h"

namespace LibGP
{
	LIBGP_INLINE void compute_edge_face_adj(
		SMatrixf& A, const MatrixXi& F)
	{
		int nv = F.maxCoeff() + 1;
		int nf = F.cols();
		int ne = -1;

		std::vector<Tripletf> coeff(3*nf);
		#pragma omp parallel for schedule(static) // reduction(max : ne)
		for (int i = 0; i < nf; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				int v0 = F(j, i), v1 = F((j + 1) % 3, i), ei = 0;
				
				double s = 1;
				if (v0 > v1)
				{
					s = 2;
					ei = v0 + v1*nv;
				}
				else
				{
					ei = v0*nv + v1;
				}

				coeff[3 * i + j] = Tripletf(ei, i, s);
			}
		}
		for (int i = 0; i < 3 * nf; i++)
		{
			if (coeff[i].row() > ne) ne = coeff[i].row();
		}

		A.resize(ne + 1, nf);
		A.reserve(VectorXi::Constant(nf, 3));
		A.setFromTriplets(coeff.begin(), coeff.end());
	}
}

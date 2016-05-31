#include "compute_mesh_laplacian.h"

namespace LibGP
{
	LIBGP_INLINE void compute_mesh_laplacian(SMatrixf& L,
		const MatrixXf& V, const MatrixXi& F,
		bool uniform = false, bool normalize = false)
	{
		int nf = F.cols();
		int nv = V.cols();

		// construct weight matrix
		std::vector<Tripletf> coeff(3 * nf + nv);
		#pragma omp parallel for
		for (int i = 0; i < nf; i++)
		{
			int v0 = F(0, i), v1 = F(1, i), v2 = F(2, i);

			// calc weight
			Vector3f weight(1, 1, 1);
			if (!uniform)
			{
				Vector3f p0 = V.col(v0);
				Vector3f p1 = V.col(v1);
				Vector3f p2 = V.col(v2);

				// sinA
				Float sinA = (p0 - p1).cross(p0 - p2).norm();
				if (sinA < EPS) sinA = EPS;

				// cosA
				Float tanA0 = (p1 - p0).dot(p2 - p0) / sinA;
				Float tanA1 = (p2 - p1).dot(p0 - p1) / sinA;
				Float tanA2 = (p1 - p2).dot(p0 - p2) / sinA;

				// weight
				weight[0] = tanA2;
				weight[1] = tanA0;
				weight[2] = tanA1;
			}

			// construct coeff
			coeff[3 * i] = Tripletf(v0, v1, weight[0]);
			coeff[3 * i + 1] = Tripletf(v1, v2, weight[1]);
			coeff[3 * i + 2] = Tripletf(v2, v0, weight[2]);
		}
		// for diag elements
		#pragma omp parallel for
		for (int i = 0; i < nv; i++)
		{
			coeff[i + 3 * nf] = Tripletf(i, i, 1);
		}

		SMatrixf mat(nv, nv);
		mat.setFromTriplets(coeff.begin(), coeff.end());
		L = 0.5*(mat + SMatrixf(mat.transpose()));

		// rectify diag elements
		#pragma omp parallel for
		for (int i = 0; i < L.outerSize(); ++i)
		{
			double sum = 0;
			double* pdiag = nullptr;
			for (SMatrixf::InnerIterator it(L, i); it; ++it)
			{
				if (it.row() == it.col())
				{
					pdiag = &(it.valueRef());
					continue;
				}
				sum += it.value();
			}
			*pdiag = - sum;

			if (normalize)
			{
				for (SMatrixf::InnerIterator it(L, i); it; ++it)
				{
					it.valueRef() /= sum;
				}
			}
		}

		if (normalize)	L = L.transpose().eval();
	}
}





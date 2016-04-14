#include "eigen_solver.h"

namespace LibGP
{
	LIBGP_INLINE void eigen_solver(	VectorXf& eig_values, MatrixXf& eig_vectors,
		const MatrixXf& A,const bool ascending)
	{
		// eigen value
		Eigen::EigenSolver<MatrixXf> ES(A);
		eig_values = ES.eigenvalues().real();
		eig_vectors = ES.eigenvectors().real();

		// selection sort
		int n = A.rows();
		for (int i = 0; i < n - 1; i++)
		{
			// find min value
			int k = i;
			Float ev = eig_values[i];
			for (int j = i + 1; j < n; j++)
			{
				bool flag = ascending ? (eig_values[j] < ev) : (eig_values[j] > ev);
				if (flag)
				{
					ev = eig_values[j];
					k = j;
				}
			}

			// swap
			eig_values[k] = eig_values[i];
			eig_values[i] = ev;
			MatrixXf vec = eig_vectors.col(k);
			eig_vectors.col(k) = eig_vectors.col(i);
			eig_vectors.col(i) = vec;
		}
	}

}

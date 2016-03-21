#include "compute_vtx_ring.h"
#include "adj_to_list.h"
#include "compute_adj_matrix.h"

LIBGP_INLINE void LibGP::compute_vtx_ring(std::vector<std::vector<int>>& vec, const Eigen::MatrixXi& F)
{
	Eigen::SparseMatrix<double> A;
	LibGP::compute_adj_matrix(A, F);
	LibGP::adj_to_list(vec, A);	
}



#include "compute_vtx_ring.h"
#include "adj_to_list.h"
#include "compute_adj_matrix.h"

namespace LibGP
{
	LIBGP_INLINE void compute_vtx_ring(vecveci& vec, const MatrixXi& F)
	{
		SMatrixf A;
		compute_adj_matrix(A, F);
		adj_to_list(vec, A);
	}
}



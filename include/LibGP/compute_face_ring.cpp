#include "compute_face_ring.h"
#include "compute_edge_face_adj.h"
#include "adj_to_list.h"

namespace LibGP
{
	LIBGP_INLINE void compute_face_ring(
		vecveci& vec, const MatrixXi& F)
	{
		SMatrixf A;
		compute_edge_face_adj(A, F);

		SMatrixf B = SMatrixf(A.transpose()) * A;
		adj_to_list(vec, B);
	}
}

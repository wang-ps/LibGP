#include "compute_face_ring.h"
#include "compute_edge_face_ring.h"
#include "compute_edge_face_adj.h"
#include "adj_to_list.h"

namespace LibGP
{
	LIBGP_INLINE void compute_face_ring(
		vecveci& vec, const MatrixXi& F)
	{
// 		SMatrixf A;
// 		compute_edge_face_adj(A, F);
// 
// 		SMatrixf B = A.transpose() * A;
// 		adj_to_list(vec, B);

		LibGP::HashEdge E2F;
		compute_edge_face_ring(E2F, F);

		vec.resize(F.cols());
		for (auto& ef : E2F)
		{
			int f0 = ef.second[0];
			int f1 = ef.second[1];
			
			// boundary edge
			if (f0 == -1 || f1 == -1) continue;

			vec[f0].push_back(f1);
			vec[f1].push_back(f0);
		}
	}
}

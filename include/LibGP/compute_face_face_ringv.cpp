#include "compute_face_face_ringv.h"
#include "compute_vtx_face_ring.h"
#include "list_to_adj.h"
#include "adj_to_list.h"

namespace LibGP
{
	LIBGP_INLINE void compute_face_face_ringv(
		vecveci& vec, const MatrixXi& F)
	{
		vecveci vf;
		compute_vtx_face_ring(vf, F);

		SMatrixf A;
		list_to_adj(A, vf);

		SMatrixf B = SMatrixf(A.transpose()) * A;

		adj_to_list(vec, B);
	}
}

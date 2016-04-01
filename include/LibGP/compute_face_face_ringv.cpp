#include "compute_face_face_ringv.h"
#include "compute_vtx_face_ring.h"
#include "list_to_adj.h"
#include "adj_to_list.h"

LIBGP_INLINE void LibGP::compute_face_face_ringv(
	std::vector<std::vector<int>>& vec,
	const Eigen::MatrixXi& F)
{
 	typedef Eigen::SparseMatrix<double> SMatrixd;

	std::vector<std::vector<int>> vf;
	LibGP::compute_vtx_face_ring(vf, F);

	SMatrixd A;
	LibGP::list_to_adj(A, vf);

	SMatrixd B = SMatrixd(A.tranpose()) * A;

	LibGP::adj_to_list(vec, B);
}
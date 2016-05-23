#pragma once
#include "libgp_global.h"

namespace LibGP
{
	LIBGP_INLINE void compute_edge_face_adj(
		SMatrixf& A, const MatrixXi& F);
}

#ifndef LIBPG_STATIC_LIBRARY
#include "compute_edge_face_adj.cpp"
#endif
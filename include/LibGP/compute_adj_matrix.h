#pragma once
#include "libgp_global.h"

namespace LibGP
{
	LIBGP_INLINE void compute_adj_matrix(
		SMatrixf& A, const MatrixXi& F);
}

#ifndef LIBPG_STATIC_LIBRARY
#include "compute_adj_matrix.cpp"
#endif
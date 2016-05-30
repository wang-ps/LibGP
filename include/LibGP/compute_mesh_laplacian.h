#pragma once
#include "libgp_global.h"

namespace LibGP
{
	LIBGP_INLINE void compute_mesh_laplacian(SMatrixf& L,
		const MatrixXf& V, const MatrixXi& F,
		bool uniform = false, bool normalize = false);
}

#ifndef LIBPG_STATIC_LIBRARY
#include "compute_mesh_laplacian.cpp"
#endif
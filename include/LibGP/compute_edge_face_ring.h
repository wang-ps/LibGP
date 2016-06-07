#pragma once
#include "libgp_global.h"

namespace LibGP
{

	LIBGP_INLINE void compute_edge_face_ring(
		std::unordered_map<int, Vector2i>& E2F,
		const MatrixXi& F);
}

#ifndef LIBPG_STATIC_LIBRARY
#include "compute_edge_face_ring.cpp"
#endif
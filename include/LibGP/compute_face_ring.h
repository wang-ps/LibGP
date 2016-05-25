#pragma once
#include "libgp_global.h"

namespace LibGP
{
	LIBGP_INLINE void compute_face_ring(
		vecveci& vec, const MatrixXi& F);
}

#ifndef LIBPG_STATIC_LIBRARY
#include "compute_face_ring.cpp"
#endif
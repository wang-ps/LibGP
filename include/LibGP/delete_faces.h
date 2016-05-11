#pragma once
#include "libgp_global.h"

namespace LibGP{
	LIBGP_INLINE void delete_faces(
		MatrixXf& V, MatrixXi& F, const VectorXb& valid_f
		);
}

#ifndef LIBPG_STATIC_LIBRARY
#include "delete_faces.cpp"
#endif
#pragma once
#include "libgp_global.h"

namespace LibGP{
	LIBGP_INLINE void delete_pieces(
		MatrixXf& V, MatrixXi& F, int min_num = 500);
}

#ifndef LIBPG_STATIC_LIBRARY
#include "delete_pieces.cpp"
#endif
#pragma once
#include "libgp_global.h"

namespace LibGP
{
	LIBGP_INLINE extern void write_ply(
		const std::string &filename, 
		const MatrixXf &V,
		const MatrixXi &F,		
		const MatrixXf &UV = MatrixXf(),
		const MatrixXu8 &C = MatrixXu8());

}

#ifndef LIBPG_STATIC_LIBRARY
#include "write_ply.cpp"
#endif
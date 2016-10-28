#pragma once
#include "libgp_global.h"

namespace LibGP
{
	LIBGP_INLINE void bounding_sphere(
		VectorXf& center, Float& radius, const MatrixXf& V);
}

#ifndef LIBPG_STATIC_LIBRARY
#include "bounding_sphere.cpp"
#endif
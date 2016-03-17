#pragma once
#include "libgp_inline.h"
#include <Eigen/Dense>

namespace LibGP
{
	template <typename Derived>
	LIBGP_INLINE void normalize_colwise(Eigen::MatrixBase<Derived>& A);
}

#ifndef LIBPG_STATIC_LIBRARY
#include "normalize_colwise.cpp"
#endif
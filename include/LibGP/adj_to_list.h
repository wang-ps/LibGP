#pragma once
#include "libgp_global.h"

namespace LibGP
{
	LIBGP_INLINE void adj_to_list(
		std::vector<std::vector<int>>& vec,
		const SMatrixf& A);
}

#ifndef LIBPG_STATIC_LIBRARY
#include "adj_to_list.cpp"
#endif
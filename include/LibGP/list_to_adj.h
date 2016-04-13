#pragma once
#include "libgp_global.h"

namespace LibGP
{
	LIBGP_INLINE void list_to_adj(
		SMatrixf& A,
		const std::vector<std::vector<int>>& vec);
}

#ifndef LIBPG_STATIC_LIBRARY
#include "list_to_adj.cpp"
#endif
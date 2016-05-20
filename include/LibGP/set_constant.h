#pragma once
#include "libgp_global.h"

namespace LibGP
{
	LIBGP_INLINE void set_constant(
		SMatrixf& smat, const Float v = 1.0);
}

#ifndef LIBPG_STATIC_LIBRARY
#include "set_constant.cpp"
#endif
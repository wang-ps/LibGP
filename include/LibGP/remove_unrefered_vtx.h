#pragma once
#include "libgp_global.h"

namespace LibGP{
	LIBGP_INLINE int remove_unrefered_vtx(
		std::string filename );
}

#ifndef LIBPG_STATIC_LIBRARY
#include "remove_unrefered_vtx.cpp"
#endif
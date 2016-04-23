#pragma once
#include "libgp_global.h"

namespace LibGP
{
	LIBGP_INLINE bool write_png(const std::string filename,
	  UINT8 *data, const int width, const int height, 
	  const bool flip = false, const bool alpha = true);
}

#ifndef LIBPG_STATIC_LIBRARY
#include "write_png.cpp"
#endif
#pragma once
#include "libgp_global.h"

namespace LibGP
{
	LIBGP_INLINE void get_all_filenames(std::vector<std::string>& _all_filenames, std::string _filename);
}

#ifndef LIBPG_STATIC_LIBRARY
#include "get_all_filenames.cpp"
#endif
#pragma once
#include "libgp_global.h"

namespace LibGP
{
	enum FileType { MODEL_FILE = 1, IMAGE_FILE, COLOR_FILE };

	LIBGP_INLINE bool get_filename(std::string& filename, bool open, FileType filetype, std::string default_name = "");
}

#ifndef LIBPG_STATIC_LIBRARY
#include "get_filename.cpp"
#endif


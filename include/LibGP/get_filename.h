#pragma once
#include "libgp_global.h"

namespace LibGP {

enum FileType { MODEL_FILE = 1, IMAGE_FILE, COLOR_FILE, ARBITRARY_FILES };

LIBGP_INLINE bool get_filename(std::string& filename, bool open,
    FileType filetype = ARBITRARY_FILES, std::string default_name = "");

}  // namespace LibGP

#ifndef LIBPG_STATIC_LIBRARY
#include "get_filename.cpp"
#endif


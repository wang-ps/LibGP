#pragma once
#include <vector>
#include <string>

namespace LibGP {
using std::vector;
using std::string;

void get_all_filenames(vector<string>& all_filenames, string filename_in);

}  // namespace LibGP

#ifndef LIBPG_STATIC_LIBRARY
#include "get_all_filenames.cpp"
#endif
#pragma once
#include <vector>
#include <string>

namespace LibGP {

using std::vector;
using std::string;

inline
void mkdir(const string& dir);

inline
string extract_path(string str);

inline
string extract_filename(string str);

inline
void get_all_filenames(vector<string>& all_filenames, const string& filename_in);

}  // namespace LibGP

#ifndef LIBPG_STATIC_LIBRARY
#include "filenames.cpp"
#endif
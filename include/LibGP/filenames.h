#pragma once
#include <vector>
#include <string>

namespace LibGP {

using std::vector;
using std::string;

void mkdir(const string& dir);
string extract_path(string str);
string extract_filename(string str);

void get_all_filenames(vector<string>& all_filenames, const string& filename_in);

}  // namespace LibGP

#ifndef LIBPG_STATIC_LIBRARY
#include "filenames.cpp"
#endif
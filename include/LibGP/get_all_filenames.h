#pragma once
#include <string>
#include <vector>

namespace LibGP
{
	void get_all_filenames(std::string& _filename, std::vector<std::string>& _all_filenames);
}

#ifndef LIBPG_STATIC_LIBRARY
#include "get_all_filenames.cpp"
#endif
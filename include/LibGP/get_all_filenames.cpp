#include "get_all_filenames.h"
#include <io.h>

LIBGP_INLINE void LibGP::get_all_filenames(std::vector<std::string>& _all_filenames, std::string _filename)
{
	// reset data
	_all_filenames.clear();

	// find
	size_t p0 = _filename.rfind('\\') + 1;
	size_t p1 = _filename.rfind('.');

	// file path
	std::string file_path(_filename, 0, p0);
	
	// get the regular expression
	_filename.replace(p0, p1-p0, "*");

	// find all the file
	_finddata_t c_file;
	intptr_t hFile = _findfirst(_filename.c_str(), &c_file);
	do
	{
		_all_filenames.push_back(file_path + std::string(c_file.name));
	} while (_findnext(hFile, &c_file) == 0);
	_findclose(hFile);
}
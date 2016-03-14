#include "get_all_filenames.h"
#include <io.h>


void get_all_filenames(std::string _filename, std::vector<std::string>& _all_filenames)
{
	// reset data
	_all_filenames.clear();

	// find
	size_t i0 = _filename.rfind('\\') + 1;
	size_t i1 = _filename.rfind('.');

	// file path
	std::string file_path(_filename, 0, i0);
	
	// get the regular expression
	_filename.replace(i0, i1, "*");

	// find all the file
	_finddata_t c_file;
	intptr_t hFile = _findfirst(_filename.c_str(), &c_file);
	do
	{
		_all_filenames.push_back(file_path + string(c_file.name));
	} while (_findnext(hFile, &c_file) == 0);
	_findclose(hFile);
}
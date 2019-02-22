#include "get_all_filenames.h"

#include <algorithm>
#include <io.h>

namespace LibGP {

string extract_path(string str) {
  std::replace(str.begin(), str.end(), '\\', '/');
  size_t pos = str.rfind('/');
  if (string::npos == pos) {
    return string(".");
  } else {
    return str.substr(0, pos);
  }
}

void get_all_filenames(vector<string>& all_filenames, string filename_in) {
  all_filenames.clear();
  string file_path = extract_path(filename_in) + "/";
  string filename = file_path + "*" + filename_in.substr(filename_in.rfind('.'));

  _finddata_t c_file;
  intptr_t hFile = _findfirst(filename.c_str(), &c_file);
  do {
    if (hFile == -1) break;
    all_filenames.push_back(file_path + string(c_file.name));
  } while (_findnext(hFile, &c_file) == 0);
  _findclose(hFile);
}

}  // namespace LibGP

#include <iostream>
#include <LibGP/read_mesh.h>
#include <LibGP/write_mesh.h>
#include <LibGP/get_all_filenames.h>
#include <LibGP/delete_pieces.h>
using namespace std;

int min_num = -1;

int main(int argc, char* argv[]) {
  if (argc < 2) return 0;
  string path_name(argv[1]);
  if (argc == 3) min_num = atoi(argv[2]);

  vector<string> filenames;
  LibGP::get_all_filenames(filenames, path_name);

  #pragma omp parallel for
  for (int i = 0; i < filenames.size(); i++) {
    cout << "Processing : " + filenames[i].substr(filenames[i].rfind('/') + 1) + "\n";

    LibGP::MatrixXf V;
    LibGP::MatrixXi F;
    LibGP::read_mesh(filenames[i], V, F);
    LibGP::delete_pieces(V, F, min_num);

    filenames[i].insert(filenames[i].rfind('.'), "_rst");
    LibGP::write_mesh(filenames[i], V, F);
  }

  return 0;
}


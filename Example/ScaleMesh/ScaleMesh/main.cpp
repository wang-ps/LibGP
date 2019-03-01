#include <iostream>
#include <string>
#include <LibGP/cmd_flags.h>
#include <LibGP/filenames.h>
#include <LibGP/read_mesh.h>
#include <LibGP/write_mesh.h>
using namespace std;

DEFINE_string(filenames, kRequired, "", "The input filenames");
DEFINE_float(scale, kRequired, 1, "The scale factor");
DEFINE_string(output_path, kOptional, ".", "The output path");
DEFINE_bool(verbose, kOptional, true, "Output logs");

int main(int argc, char* argv[]) {
  bool succ = cflags::ParseCmd(argc, argv);
  if (!succ) {
    cflags::PrintHelpInfo("\nUsage: ScaleMesh.exe");
    return 0;
  }

  string file_path = FLAGS_filenames;
  string output_path = FLAGS_output_path;
  if (output_path != ".") LibGP::mkdir(output_path);
  else output_path = LibGP::extract_path(file_path);
  output_path += "/";

  vector<string> all_files;
  LibGP::get_all_filenames(all_files, file_path);

  #pragma omp parallel for
  for (int i = 0; i < all_files.size(); i++) {
    // get filename
    string filename = LibGP::extract_filename(all_files[i]);
    if (FLAGS_verbose) cout << "Processing: " + filename + "\n";

    LibGP::MatrixXf V; LibGP::MatrixXi F;
    LibGP::read_mesh(all_files[i], V, F);

    V *= FLAGS_scale;
    LibGP::write_mesh(output_path + filename + ".obj", V, F);
  }

  return 0;
}
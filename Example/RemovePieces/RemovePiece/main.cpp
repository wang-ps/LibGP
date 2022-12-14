#include <iostream>
#include <LibGP/read_mesh.h>
#include <LibGP/write_mesh.h>
#include <LibGP/filenames.h>
#include <LibGP/delete_pieces.h>
#include <LibGP/cmd_flags.h>

using namespace std;

DEFINE_string(filenames, kOptional, "", "The input filenames");
DEFINE_string(filename, kOptional, "", "The input filenames");
DEFINE_string(output_path, kOptional, ".", "The output path");
DEFINE_int(min_num, kOptional, -1, "Min piece number");
DEFINE_bool(verbose, kOptional, true, "Output logs");

int main(int argc, char* argv[]) {
  bool succ = cflags::ParseCmd(argc, argv);
  if (!succ) {
    cflags::PrintHelpInfo("\nUsage: DeletePiece");
    return 0;
  }

  vector<string> filenames;
  string file_path = FLAGS_filenames;
  if (!file_path.empty()) {
    LibGP::get_all_filenames(filenames, file_path);
  } else {
    file_path = FLAGS_filename;
    filenames.push_back(file_path);
    assert(file_path != "");
  }

  string output_path = FLAGS_output_path;
  if (output_path != ".") { LibGP::mkdir(output_path); }
  else { output_path = LibGP::extract_path(file_path); }
  output_path += "/";

  #pragma omp parallel for
  for (int i = 0; i < filenames.size(); i++) {
    LibGP::MatrixXf V;
    LibGP::MatrixXi F;
    LibGP::read_mesh(filenames[i], V, F);
    LibGP::delete_pieces(V, F, FLAGS_min_num);

    string filename = LibGP::extract_filename(filenames[i]);
    if (FLAGS_verbose) cout << "Processing : " + filename + "\n";
    filename = output_path + filename + ".obj";
    LibGP::write_mesh(filename, V, F);
  }

  return 0;
}


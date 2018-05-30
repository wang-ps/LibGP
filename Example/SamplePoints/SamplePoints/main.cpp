#include <string>
#include <fstream>
#include <iostream>
#include <Eigen/dense>
#include <LibGP/read_mesh.h>
#include <LibGP/sample_points.h>
#include <LibGP/get_all_filenames.h>
using namespace std;

bool write_points(const string filename, const Eigen::MatrixXf& pts, const Eigen::MatrixXf& normals) {
  ofstream outfile(filename, ofstream::binary);
  if (!outfile) {
    cout << "Opening file failed" << filename << endl;
    return false;
  }
  int n = pts.cols();
  outfile.write((char*)(&n), sizeof(int));
  outfile.write((char*)pts.data(), sizeof(float)*pts.size());
  outfile.write((char*)normals.data(), sizeof(float)*normals.size());
  outfile.close();
  return true;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    cout << "Usage: Octree2PtCloud.exe <input file path> [output file path] [area]\n";
    return 0;
  }

  float area = 2.0f;
  string input_file_path(argv[1]);
  string output_file_path(input_file_path);
  if (argc > 2) output_file_path = argv[2];
  if (argc > 3) area = atof(argv[3]);

  vector<string> all_files;
  LibGP::get_all_filenames(all_files, input_file_path + "\\*.ply");

  for (int i = 0; i < all_files.size(); ++i) {
    string filename = all_files[i];
    unsigned p1 = filename.rfind('\\');
    unsigned p2 = filename.rfind('.');
    
    Eigen::MatrixXf V; Eigen::MatrixXi F;
    LibGP::read_mesh(filename, V, F);

    Eigen::MatrixXf pts, normals;
    LibGP::sample_points(pts, normals, V, F, 2.0);

    string filename_points = output_file_path + filename.substr(p1, p2 - p1) + ".points";
    write_points(filename_points, pts, normals);
  }

  return 0;
}


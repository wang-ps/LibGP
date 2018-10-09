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
    cout << "Usage: Octree2PtCloud.exe <input filenames> [output file path] [area]\n";
    return 0;
  }

  float area = 0.5f;
  string input_filenames(argv[1]);
  string output_file_path = input_filenames.substr(0, input_filenames.rfind('\\'));
  if (argc > 2) output_file_path = argv[2];
  if (argc > 3) area = atof(argv[3]);

  vector<string> all_files;
  LibGP::get_all_filenames(all_files, input_filenames);

  for (int i = 0; i < all_files.size(); ++i) {
    string filename = all_files[i];
    unsigned p1 = filename.rfind('\\');
    unsigned p2 = filename.rfind('.');

    Eigen::MatrixXf V; Eigen::MatrixXi F;
    LibGP::read_mesh(filename, V, F);

    Eigen::MatrixXf pts, normals;
    LibGP::sample_points(pts, normals, V, F, area);

    filename = filename.substr(p1, p2 - p1);
    //cout << filename << endl;
    if (i % 10 == 0) cout << i << " ";
    if (i % 100 == 0) cout << "\n";
    string filename_points = output_file_path + filename + ".points";
    write_points(filename_points, pts, normals);
  }
  cout << endl;

  return 0;
}


#include <iostream>
#include <string>
#include <LibGP/cmd_flags.h>
#include <LibGP/read_obj.h>
#include <LibGP/write_obj.h>
#include <LibGP/bounding_sphere.h>
using namespace std;

DEFINE_string(filename_a, kRequired, "", "The input filename");
DEFINE_string(filename_b, kRequired, "", "The input filename");
DEFINE_string(filename_o, kOptional, ".", "The output filename");
DEFINE_bool(verbose, kOptional, true, "Output logs");


int main(int argc, char* argv[]) {
  bool succ = cflags::ParseCmd(argc, argv);
  if (!succ) {
    cflags::PrintHelpInfo("\nUsage: ScaleMesh.exe");
    return 0;
  }

  // load
  LibGP::MatrixXf Va, Vb;
  LibGP::MatrixXi Fa, Fb;
  bool succ_a = LibGP::read_obj(FLAGS_filename_a, Va, Fa);
  bool succ_b = LibGP::read_obj(FLAGS_filename_b, Vb, Fb);

  // check
  if (succ_a == false) {
    cout << "Can not load " << FLAGS_filename_a << endl;
    return 0;
  }
  if (succ_b == false) {
    cout << "Can not load " << FLAGS_filename_b << endl;
    return 0;
  }

  // scale mesh
  LibGP::VectorXf center_a, center_b;
  LibGP::Float radius_a, radius_b;
  LibGP::bounding_sphere(center_a, radius_a, Va);
  LibGP::bounding_sphere(center_b, radius_b, Vb);

  Va.colwise() -= center_a;
  Va *= 1.0f / (radius_a + 1.0e-10f);
  Vb.colwise() -= center_b;
  Vb *= 1.0f / (radius_b + 1.0e-10f);

  // displace index
  int nv = Va.cols();
  Fb = (Fb.array() + nv).matrix();

  // concat
  LibGP::MatrixXf Vo(Va.rows(), Va.cols() + Vb.cols());
  Vo << Va, Vb;
  LibGP::MatrixXi Fo(Fa.rows(), Fa.cols() + Fb.cols());
  Fo << Fa, Fb;

  // output
  bool succ_o = LibGP::write_obj(FLAGS_filename_o, Vo, Fo);
  if (succ_o == false) {
    cout << "Can not write " << FLAGS_filename_o << endl;
  }

  return 0;
}
#include <iostream>
#include <LibGP/read_mesh.h>
#include <LibGP/write_mesh.h>
#include <LibGP/bilateral_normal_filter.h>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 3) return 0;
	
	string filename(argv[1]), filename1(argv[2]);
	Eigen::MatrixXd V;
	Eigen::MatrixXi F;
	LibGP::read_mesh(filename, V, F);

	Eigen::MatrixXd V1;
	LibGP::bilateral_normal_filter(V1, V, F);

	LibGP::write_mesh(filename1, V1, F);

	return 0;
}
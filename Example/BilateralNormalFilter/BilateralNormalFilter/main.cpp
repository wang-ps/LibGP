#include <iostream>
#include <LibGP/read_mesh.h>
#include <LibGP/write_mesh.h>
#include <LibGP/bilateral_normal_filter.h>
using namespace std;

int main()
{
	string filename = "C:\\Users\\wps\\Desktop\\MLDenoise\\Noisy\\fandisk_n2.obj";
	Eigen::MatrixXd V;
	Eigen::MatrixXi F;
	LibGP::read_mesh(filename, V, F);

	Eigen::MatrixXd V1;
	LibGP::bilateral_normal_filter(V1, V, F);

	string filename1 = "C:\\Users\\wps\\Desktop\\fandisk_n2.obj";
	LibGP::write_mesh(filename1, V1, F);

	return 0;
}
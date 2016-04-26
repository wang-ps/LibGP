#include <iostream>
#include <LibGP/read_mesh.h>
#include <LibGP/write_mesh.h>
#include <LibGP/bilateral_normal_filter.h>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 2) return 0;
	for (int i = 1; i < argc; i++)
	{
		string filename(argv[i]);

		Eigen::MatrixXd V; Eigen::MatrixXi F;
		LibGP::read_mesh(filename, V, F);

		Eigen::MatrixXd V1;
		LibGP::bilateral_normal_filter(V1, V, F, 0.35, 1, 3);

		filename.insert(filename.rfind('.'), "_bilateral");
		LibGP::write_mesh(filename, V1, F);
	}

	return 0;
}
#include <iostream>
#include <vector>
#include <LibGP/libgp.h>
#include <Eigen/dense>
using namespace Eigen;
using namespace std;

void remove_pieces(MatrixXd& V, MatrixXi& F, int num);
int min_num = 500;

int main(int argc, char* argv[])
{
	if (argc < 2) return 0;
	string path_name(argv[1]);
	if (argc == 3) min_num = atoi(argv[2]);

	path_name += "\\*.obj";
	vector<string> filenames;
	LibGP::get_all_filenames(filenames, path_name);

	#pragma omp parallel for
	for (int i = 0; i < filenames.size(); i++)
	{
		MatrixXd V; MatrixXi F;
		LibGP::read_mesh(filenames[i], V, F);
		LibGP::delete_pieces(V, F, min_num);

		filenames[i].insert(filenames[i].rfind('.'), "_rst");
		LibGP::write_mesh(filenames[i], V, F);
	}
	return 0;
}


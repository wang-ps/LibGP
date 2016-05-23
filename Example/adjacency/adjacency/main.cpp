#include <iostream>
#include <libGP/LibGP.h>

using namespace Eigen;
using namespace std;

int main(int argc, char* argv[])
{
	MatrixXd V;
	MatrixXi F;
	SparseMatrix<double> A, B;

	LibGP::read_obj(argv[1], V, F);
	cout << F << endl;

	LibGP::compute_vtx_adj(A, F);
	cout << endl << A << endl;

	LibGP::compute_edge_face_adj(B, F);
	cout << endl << B << endl;

	std::vector<std::vector<int>> vec;
	LibGP::adj_to_list(vec, A);
	for (int i = 0; i < vec.size(); i++)
	{
		cout << endl;
		for (int j = 0; j < vec[i].size(); j++)
		{
			cout << vec[i][j] << " ";
		}
	}
	cout << endl;

	return 0;
}
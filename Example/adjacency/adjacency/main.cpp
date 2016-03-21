#include <iostream>
#include <libGP/read_obj.h>
#include <libGP/compute_adj_matrix.h>
#include <libGP/adj_to_list.h>
#include <Eigen/Dense>
#include <Eigen/Sparse>
using namespace Eigen;
using namespace std;

int main(int argc, char* argv[])
{
	MatrixXd V;
	MatrixXi F;
	SparseMatrix<double> A;

	LibGP::read_obj(argv[1], V, F);
	cout << F << endl;

	LibGP::compute_adj_matrix(A, F);
	cout << endl << A << endl;

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
#include <LibGP/libgp.h>
#include <iostream>
#include <time.h>
using namespace std;
using namespace Eigen;

int main(int argc, char* argv[])
{
	if (argc < 3) return 0;

	string filename(argv[1]);
	MatrixXd V; MatrixXi F;
	LibGP::read_mesh(filename, V, F);
	
	string filename1(argv[2]);
	MatrixXd V1; MatrixXi F1;
	LibGP::read_mesh(filename1, V1, F1);
	
	MatrixXd N1;
	LibGP::compute_face_normal(N1, V1, F);

	clock_t t1 = clock();
	LibGP::PoissonDeformation deformation(V, F);
	clock_t t2 = clock();
	cout << "Factorization time : " << t2 - t1 << endl;

	t1 = clock();
	MatrixXd V2;
	deformation.deform(V2, N1);
	t2 = clock();
	cout << "Deform time : " << t2 - t1 << endl;

	string filename2 = filename;
	filename2.insert(filename.rfind('.'), "_poisson");
	LibGP::write_mesh(filename2, V2, F);

	return 0;
}
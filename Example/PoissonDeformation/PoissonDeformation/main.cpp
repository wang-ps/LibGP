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

namespace LibGP
{
	LIBGP_INLINE void compute_mesh_laplacian(SMatrixf& L,
		const MatrixXf& V, const MatrixXi& F,
		bool uniform = false, bool normalize = false)
	{
		int nf = F.cols();
		int nv = V.cols();

		// compute weight
		VectorXf weight = VectorXf::Ones(3 * nf);
		if (!uniform)
		{
			#pragma omp parallel for
			for (int i = 0; i < nf; i++)
			{
				Vector3f p0 = V.col(F(0, i));
				Vector3f p1 = V.col(F(1, i));
				Vector3f p2 = V.col(F(2, i));

				// sinA
				Float sinA = (p0 - p1).cross(p0 - p2).norm();
				if (sinA < EPS) sinA = EPS;

				// cosA
				Float tanA0 = (p1 - p0).dot(p2 - p0) / sinA;
				Float tanA1 = (p2 - p1).dot(p0 - p1) / sinA;
				Float tanA2 = (p1 - p2).dot(p0 - p2) / sinA;

				// weight
				weight[3 * i] = tanA2;
				weight[3 * i + 1] = tanA0;
				weight[3 * i + 2] = tanA1;
			}
		}

		// construct weight matrix
		std::vector<Tripletf> coeff(3 * nf);
		for (int i = 0; i < nf; i++)
		{

		}
	
	}
}

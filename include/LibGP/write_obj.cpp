#include "write_obj.h"


LIBGP_INLINE bool LibGP::write_obj(std::string filename, Eigen::MatrixXd& V, Eigen::MatrixXi& F)
{
	std::ofstream outfile(filename, std::ios::binary);
	if (!outfile)
	{
		std::cout << "Open OBJ file error!" << std::endl;
		return false;
	}

	// turn to string
	std::vector<char[128]> vec1(V.cols());
#pragma omp parallel for 
	for (int i = 0; i < V.cols(); i++)
	{
		sprintf(vec1[i], "v %.6lf %.6lf %.6lf\n", V(0, i), V(1, i), V(2, i));
	}

	std::vector<char[128]> vec2(F.cols());
#pragma omp parallel for 
	for (int i = 0; i < F.cols(); i++)
	{
		sprintf(vec2[i], "f %d %d %d\n", F(0, i) + 1, F(1, i) + 1, F(2, i) + 1);
	}

	// concat
	std::string str;
	for (int i = 0; i < V.cols(); str += vec1[i++]);
	for (int i = 0; i < F.cols(); str += vec2[i++]);
		 
	// write into file
	outfile.write(str.data(), str.size());

	// close file
	outfile.close();
	return true;

	// 
	// 	// write into file
	// 	outfile.write(str.data(), str.size());

	// 	//std::setprecision(9)
	// 	outfile << std::fixed ;
	// 	for (int i = 0; i < V.cols(); i++)
	// 	{
	// 		outfile << "v " << V(0, i) << ' ' << V(1, i) << ' ' << V(2, i) << "\n";
	// 	}
	// 
	// 	for (int i = 0; i < F.cols(); i++)
	// 	{
	// 		outfile << "f " << F(0, i) + 1 << ' ' << F(1, i) + 1 << ' ' << F(2, i) + 1 << "\n";
	// 	}
}
#include "read_off.h"
#include <fstream>

LIBGP_INLINE bool LibGP::write_off(std::string filename, Eigen::MatrixXd& V, Eigen::MatrixXi& F)
{
	std::ofstream outfile(filename, std::ios::binary);

	if (!outfile)
	{
		std::cout << "Open OFF file error!" << std::endl;
		return false;
	}

	// output header
	outfile << "OFF\n";
	outfile << V.cols() << ' ' << F.cols() << " 0 \n";

	// turn to string
	std::vector<char[128]> vec1(V.cols());
#pragma omp parallel for 
	for (int i = 0; i < V.cols(); i++)
	{
		sprintf(vec1[i], "%.6lf %.6lf %.6lf\n", V(0, i), V(1, i), V(2, i));
	}

	std::vector<char[128]> vec2(F.cols());
#pragma omp parallel for 
	for (int i = 0; i < F.cols(); i++)
	{
		sprintf(vec2[i], "3 %d %d %d\n", F(0, i), F(1, i), F(2, i));
	}

	// concat
	std::string str;
	for (int i = 0; i < V.cols(); str += vec1[i++]);
	for (int i = 0; i < F.cols(); str += vec2[i++]);

	// write into file
	outfile.write(str.data(), str.size());

	outfile.close();
	return true;

// 	// output vertex
// 	outfile << std::fixed;
// 	for (int i = 0; i < V.cols(); i++)
// 	{
// 		outfile << V(0, i) << ' ' << V(1, i) << ' ' << V(2, i) << " \n";
// 	}
// 
// 	// output face
// 	// output vertex
// 	outfile << std::fixed;
// 	for (int i = 0; i < F.cols(); i++)
// 	{
// 		outfile << "3 " << F(0, i) << ' ' << F(1, i) << ' ' << F(2, i) << " \n";
// 	}

}
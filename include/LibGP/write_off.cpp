#include "read_off.h"
#include <fstream>

LIBGP_INLINE bool LibGP::write_off(std::string filename, Eigen::MatrixXd& V, Eigen::MatrixXi& F)
{
	std::ofstream outfile(filename);

	if (!outfile)
	{
		std::cout << "Open OFF file error!" << std::endl;
		return false;
	}

	// output header
	outfile << "OFF\n";
	outfile << V.cols() << ' ' << F.cols() << " 0 \n";

	// output vertex
	outfile << std::fixed;
	for (int i = 0; i < V.cols(); i++)
	{
		outfile << V(0, i) << ' ' << V(1, i) << ' ' << V(2, i) << " \n";
	}

	// output face
	// output vertex
	outfile << std::fixed;
	for (int i = 0; i < F.cols(); i++)
	{
		outfile << "3 " << F(0, i) << ' ' << F(1, i) << ' ' << F(2, i) << " \n";
	}

	outfile.close();
	return true;
}
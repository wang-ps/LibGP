#include <fstream>
#include <iostream>
#include "write_obj.h"


LIBGP_INLINE bool LibGP::write_obj(std::string filename, Eigen::MatrixXd& V, Eigen::MatrixXi& F)
{
	std::ofstream outfile(filename, std::ios::binary);
	if (!outfile)
	{
		std::cout << "Open OBJ file error!" << std::endl;
		return false;
	}

	//std::setprecision(9)
	outfile << std::fixed ;
	for (int i = 0; i < V.cols(); i++)
	{
		outfile << "v " << V(0, i) << ' ' << V(1, i) << ' ' << V(2, i) << "\n";
	}

	for (int i = 0; i < F.cols(); i++)
	{
		outfile << "f " << F(0, i) + 1 << ' ' << F(1, i) + 1 << ' ' << F(2, i) + 1 << "\n";
	}

	outfile.close();
	return true;
}
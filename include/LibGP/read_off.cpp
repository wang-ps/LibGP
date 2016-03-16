#include "read_off.h"
#include <fstream>


LIBGP_INLINE bool LibGP::read_off(std::string filename, Eigen::MatrixXd& V, Eigen::MatrixXi& F)
{
	std::ifstream infile(filename);

	if (!infile)
	{
		std::cout << "Open OFF file error!" << std::endl;
		return false;
	}

	// eat head
	std::string head;
	infile >> head;

	// face/vertex number
	int nv, nf, ne;
	infile >> nv >> nf >> ne;

	// load vertex
	V.resize(3, nv);
	for (int i = 0; i < nv; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			infile >> V(j, i);
		}
	}

	// load face
	F.resize(3, nf);
	for (int i = 0; i < nf; i++)
	{
		int tmp;
		infile >> tmp;
		for (int j = 0; j < 3; j++)
		{
			infile >> F(j, i);
		}
	}

	infile.close();
	return true;
}

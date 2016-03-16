#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include "read_obj.h"


LIBGP_INLINE bool LibGP::read_obj(std::string filename, Eigen::MatrixXd& V, Eigen::MatrixXi& F)
{
	std::ifstream infile(filename, std::ifstream::binary);
	if (!infile)
	{
		std::cerr << "Open OBJ file error!" << std::endl;
		return false;
	}

	// get length of file
	infile.seekg(0, infile.end);
	int len = infile.tellg();
	infile.seekg(0, infile.beg);

	// load the file into memory
	char* buffer = new char[len+1];
	infile.read(buffer, len);
	buffer[len] = 0;
	infile.close();

	// V and F buffer
	std::vector<double> vecV;
	std::vector<int> vecF;

	// parse the buffer
	std::string line, keywrd;
	std::istringstream instring(buffer);
	while (!instring.eof())
	{
		std::getline(instring, line);
		std::istringstream linestream(line);
		linestream >> keywrd;

		if (keywrd == "v")
		{
			double x;
			for (int i = 0; i < 3; i++)
			{
				linestream >> x;
				vecV.push_back(x);
			}
		}

		if (keywrd == "f")
		{
			int v;
			std::string tmp;
			size_t found = line.find('/', 1);
			for (int i = 0; i < 3; i++)
			{
				linestream >> v;
				if (found != std::string::npos)
				{
					linestream >> tmp;
				}
				vecF.push_back(v - 1);
			}
		}
	}

	// output
	V.resize(3, vecV.size() / 3);
	std::memcpy(V.data(), vecV.data(), vecV.size()*sizeof(double));

	F.resize(3, vecF.size() / 3);
	std::memcpy(F.data(), vecF.data(), vecF.size()*sizeof(int));

	// release
	delete[] buffer;
	return true;
}
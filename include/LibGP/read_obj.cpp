#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <omp.h>
#include "read_obj.h"


LIBGP_INLINE bool LibGP::read_obj(std::string filename, Eigen::MatrixXd& V, Eigen::MatrixXi& F)
{
	std::ifstream infile(filename, std::ifstream::binary);
	if (!infile)
	{
		std::cout << "Open OBJ file error!" << std::endl;
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

	// parse buffer data
	std::vector<char*> pVline, pFline;
	for (int i = 0; i < len; i++)
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
		}
		else if (buffer[i] == 'v' && buffer[i + 1] == ' ')
		{
			buffer[i] = 0;
			pVline.push_back(buffer + i + 2);
		}
		else if (buffer[i] == 'f' && buffer[i + 1] == ' ')
		{
			buffer[i] = 0;
			pFline.push_back(buffer + i + 2);
		}
	}
	
	// load V
	V.resize(3, pVline.size());
	#pragma omp parallel for
	for (int i = 0; i < pVline.size(); i++)
	{
		std::istringstream instr(pVline[i]);
		instr >> V(0, i) >> V(1, i) >> V(2, i);
	}

	// load F
	F.resize(3, pFline.size());
	#pragma omp parallel for
	for (int i = 0; i < pFline.size(); i++)
	{
		std::istringstream instr(pFline[i]);
		char* found = strchr(pFline[i], '/');
		for (int j = 0; j < 3; j++)
		{
			instr >> F(j, i);
			F(j, i) -= 1;
			std::string tmp;
			if (found != nullptr)
			{
				instr >> tmp;
			}
		}
	}

	// release
	delete[] buffer;
	return true;
}
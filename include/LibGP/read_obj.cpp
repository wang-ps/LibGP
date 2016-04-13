#include "read_obj.h"

namespace LibGP
{
	LIBGP_INLINE bool LibGP::read_obj(std::string filename, MatrixXf& V, MatrixXi& F)
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
		char* buffer = new char[len + 1];
		infile.read(buffer, len);
		buffer[len] = 0;
		infile.close();

		// parse buffer data
		std::vector<char*> pVline, pFline;
		char* pch = strtok(buffer, "\n");
		while (pch != nullptr)
		{
			if (pch[0] == 'v' && pch[1] == ' ')
			{
				pVline.push_back(pch + 2);
			}
			else if (pch[0] == 'f' && pch[1] == ' ')
			{
				pFline.push_back(pch + 2);
			}

			pch = strtok(nullptr, "\n");
		}

		// load V
		V.resize(3, pVline.size());
		#pragma omp parallel for
		for (int i = 0; i < pVline.size(); i++)
		{
			char* p = strtok(pVline[i], " ");
			for (int j = 0; j < 3; j++)
			{
				V(j, i) = atof(p);
				p = strtok(nullptr, " ");
			}
		}

		// load F
		F.resize(3, pFline.size());
		#pragma omp parallel for
		for (int i = 0; i < pFline.size(); i++)
		{
			char* p = strtok(pFline[i], " ");
			for (int j = 0; j < 3; j++)
			{
				F(j, i) = atoi(p) - 1;
				p = strtok(nullptr, " ");
			}
		}

		// release
		delete[] buffer;
		return true;
	}
}
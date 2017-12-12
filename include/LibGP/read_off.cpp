#include "read_off.h"

namespace LibGP
{
	LIBGP_INLINE bool LibGP::read_off(std::string filename, MatrixXf& V, MatrixXi& F)
	{
		std::ifstream infile(filename, std::ios::binary);
		if (!infile)
		{
			std::cout << "Open " + filename + " error!" << std::endl;
			return false;
		}

		// eat head
		std::string head;
		infile >> head;
		if (!(head == "OFF"))
		{
			std::cout << filename + " is not an OFF file!" << std::endl;
			return false;
		}

		// face/vertex number
		int nv, nf, ne;
		infile >> nv >> nf >> ne;

		// get length of file
		int p1 = infile.tellg();
		infile.seekg(0, infile.end);
		int p2 = infile.tellg();
		infile.seekg(p1, infile.beg);
		int len = p2 - p1;

		// load the file into memory
		char* buffer = new char[len + 1];
		infile.read(buffer, len);
		buffer[len] = 0;

		// close file
		infile.close();

		// parse buffer data
		std::vector<char*> pV;
		pV.reserve(3 * nv);
		char* pch = strtok(buffer, " \r\n");
		pV.push_back(pch);
		for (int i = 1; i < 3 * nv; i++)
		{
			pch = strtok(nullptr, " \r\n");
			pV.push_back(pch);
		}
		std::vector<char*> pF;
		pF.reserve(3 * nf);
		for (int i = 0; i < nf; i++)
		{
			// eat the first data
			pch = strtok(nullptr, " \r\n");
			for (int j = 0; j < 3; j++)
			{
				pch = strtok(nullptr, " \r\n");
				pF.push_back(pch);
			}
		}

		// load vertex
		V.resize(3, nv);
		Float* p = V.data();
		#pragma omp parallel for
		for (int i = 0; i < 3 * nv; i++)
		{
			*(p + i) = atof(pV[i]);
		}

		// load face
		F.resize(3, nf);
		int* q = F.data();
		#pragma omp parallel for
		for (int i = 0; i < 3 * nf; i++)
		{
			*(q + i) = atoi(pF[i]);
		}

		//release
		delete[] buffer;
		return true;
	}
}



// LIBGP_INLINE bool LibGP::read_off(std::string filename, MatrixXf& V, MatrixXi& F)
// {
// 	std::ifstream infile(filename);
// 
// 	if (!infile)
// 	{
// 		std::cout << "Open OFF file error!" << std::endl;
// 		return false;
// 	}
// 
// 	// eat head
// 	std::string head;
// 	infile >> head;
// 
// 	// face/vertex number
// 	int nv, nf, ne;
// 	infile >> nv >> nf >> ne;
// 
// 	// load vertex
// 	V.resize(3, nv);
// 	for (int i = 0; i < nv; i++)
// 	{
// 		for (int j = 0; j < 3; j++)
// 		{
// 			infile >> V(j, i);
// 		}
// 	}
// 
// 	// load face
// 	F.resize(3, nf);
// 	for (int i = 0; i < nf; i++)
// 	{
// 		int tmp;
// 		infile >> tmp;
// 		for (int j = 0; j < 3; j++)
// 		{
// 			infile >> F(j, i);
// 		}
// 	}
// 
// 	infile.close();
// 	return true;
// }

#include "mex.h"
#include <cstring>
#include <fstream>
#include <vector>
#include <omp.h>

// [V, F] = read_obj(filename);
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	/* check input and output */
	if (nlhs != 2)
	{
		mexErrMsgIdAndTxt("LibGP:read_obj:nlhs",
			"Two outputs required.");
	}
	if (nrhs != 1)
	{
		mexErrMsgIdAndTxt("LibGP:read_obj:nrhs",
			"One input required.");
	}

	/* Input : filename */
	char filename[512];
	mxGetString(prhs[0], filename, mxGetN(prhs[0]) + 1);

	/* read obj file */
	std::ifstream infile(filename, std::ifstream::binary);
	if (!infile)
	{
		mexErrMsgIdAndTxt("LibGP:read_obj:read_file",
			"Opening input file failed.");
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

	/* parse buffer data */
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

	/* Output : V */
	plhs[0] = mxCreateDoubleMatrix(3, pVline.size(), mxREAL);
	double* pV = (double*)mxGetData(plhs[0]);
	#pragma omp parallel for
	for (int i = 0; i < pVline.size(); i++)
	{
		char* p = strtok(pVline[i], " ");
		for (int j = 0; j < 3; j++)
		{
			pV[j + 3 * i] = atof(p);
			p = strtok(nullptr, " ");
		}
	}

	/* Output : F */
	plhs[1] = mxCreateNumericMatrix(3, pFline.size(), mxINT32_CLASS, mxREAL);
	int* pF = (int*)mxGetData(plhs[1]);
	#pragma omp parallel for
	for (int i = 0; i < pFline.size(); i++)
	{
		char* p = strtok(pFline[i], " ");
		for (int j = 0; j < 3; j++)
		{
			pF[j + 3 * i] = atoi(p);
			p = strtok(nullptr, " ");
		}
	}

	delete[] buffer;
}
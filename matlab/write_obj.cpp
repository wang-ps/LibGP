#include "mex.h"
#include <cstring>
#include <fstream>
#include <vector>
#include <omp.h>

// succ =  write_mesh(filename, V, F);
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	/* check input and output */
	if (nrhs != 3)
	{
		mexErrMsgIdAndTxt("LibGP:read_obj:nrhs",
			"Three inputs required.");
	}

	/* Input */
	char filename[512];
	mxGetString(prhs[0], filename, mxGetN(prhs[0]) + 1);
	std::ofstream outfile(filename, std::ios::binary);
	if (!outfile)
	{
		mexErrMsgIdAndTxt("LibGP:write_obj:write_file",
		"Opening file failed.");
	}

	// turn to string
	int nv = mxGetN(prhs[1]);
	double* pv = (double*)mxGetData(prhs[1]);
	std::vector<char[128]> vec1(nv);
	#pragma omp parallel for 
	for (int i = 0; i < nv; i++)
	{
		sprintf(vec1[i], "v %.6lf %.6lf %.6lf\n", 
			pv[3 * i], pv[3 * i + 1], pv[3 * i + 2]);
	}

	int nf = mxGetN(prhs[2]);
	std::vector<char[128]> vec2(nf);
	mxClassID  category = mxGetClassID(prhs[2]);
	if (category == mxINT32_CLASS)
	{
		int* pf = (int*)mxGetData(prhs[2]);
		#pragma omp parallel for 
		for (int i = 0; i < nf; i++)
		{
			sprintf(vec2[i], "f %d %d %d\n", 
				pf[3 * i], pf[3 * i + 1], pf[3 * i + 2]);
		}
	}
	else if (category == mxDOUBLE_CLASS)
	{
		double* pf = (double*)mxGetData(prhs[2]);
		#pragma omp parallel for 
		for (int i = 0; i < nf; i++)
		{
			sprintf(vec2[i], "f %d %d %d\n", 
				(int) pf[3 * i], (int)pf[3 * i + 1], (int)pf[3 * i + 2]);
		}
	}
	else
	{
		mexErrMsgIdAndTxt("LibGP:write_obj:type",
			"F data type error.");
	}

	// concat
	std::string str;
	for (int i = 0; i < nv; str += vec1[i++]);
	for (int i = 0; i < nf; str += vec2[i++]);

	// write into file
	outfile.write(str.data(), str.size());
	// close file
	outfile.close();
}
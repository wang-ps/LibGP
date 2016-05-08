#include "mex.h"
#include <Eigen/dense>
#include <LibGP/reconstruct_mesh_LS.h>

// V1 =  reconstruct_mesh_local(V, F, N1, it_num);
// NOTE : type of F must be int32
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	/* check input */
	if (nrhs < 3)
	{
		mexErrMsgIdAndTxt("LibGP:reconstruct_mesh_local:nrhs",
			"At least three inputs required.");
	}

	/* Input */
	// get V
	int nv = mxGetN(prhs[0]);
	double* pv = (double*)mxGetData(prhs[0]);
	Eigen::MatrixXd V = Eigen::Map<Eigen::MatrixXd>(pv, 3, nv);

	// get F
	int nf = mxGetN(prhs[1]);
	int* pf = (int*)mxGetData(prhs[1]);
	Eigen::MatrixXi F = Eigen::Map<Eigen::MatrixXi>(pf, 3, nf).array() - 1;

	// get N1
	double* pn = (double*)mxGetData(prhs[2]);
	Eigen::MatrixXd N1 = Eigen::Map<Eigen::MatrixXd>(pn, 3, nf);

	// get it_num
	int it_num = 20;
	if (nrhs == 4)
	{
		double* tmp = (double*)mxGetData(prhs[3]);
		it_num = int(*tmp);
	}

	/* Reconstruct */
	Eigen::MatrixXd V1;
	LibGP::reconstruct_mesh_LS(V1, V, F, N1, it_num);

	/* Output */
	plhs[0] = mxCreateDoubleMatrix(3, nv, mxREAL);
	double* pv1 = (double*)mxGetData(plhs[0]);
	memcpy(pv1, V1.data(), sizeof(double)*V1.size());
}
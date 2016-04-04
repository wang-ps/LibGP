#include "slice.h"

LIBGP_INLINE void LibGP::slice(Eigen::MatrixXd& B, LibGP::VectorXb& flag, const Eigen::MatrixXd& A)
{
	assert(A.cols() == flag.size());

	int n = 0;
	for (int i = 0; i < flag.size(); n += flag[i++]);

	B.resize(A.rows(), n);
	for (int i = 0, j = 0; i < flag.rows(); i++)
	{
		if (flag[i])
		{
			B.col(j++) = A.col(i);
		}
	}
}

LIBGP_INLINE void LibGP::slice_into(Eigen::MatrixXd& A, LibGP::VectorXb& flag, const Eigen::MatrixXd& B)
{
	assert(A.cols() == flag.size());

	for (int i = 0, j = 0; i < flag.size(); i++)
	{
		if (flag[i])
		{
			A.col(i) = B.col(j++);
		}
	}
}


LIBGP_INLINE void LibGP::slice(Eigen::MatrixXd& B, std::vector<int>& idx, const Eigen::MatrixXd& A)
{
	B.resize(A.rows(), idx.size());
	for (int i = 0; i < idx.size(); i++)
	{
		B.col(i) = A.col(idx[i]);
	}
}

LIBGP_INLINE void LibGP::slice_into(Eigen::MatrixXd& A, std::vector<int>& idx, const Eigen::MatrixXd& B)
{
	for (int i = 0; i < idx.size(); i++)
	{
		A.col(idx[i]) = B.col(i);
	}
}

LIBGP_INLINE void LibGP::slice_into(Eigen::VectorXi& A, LibGP::VectorXb& flag, const int b)
{
	assert(A.rows() == flag.size());

	for (int i = 0; i < flag.size(); i++)
	{
		if (flag[i]) A[i] = b;
	}
}

LIBGP_INLINE void LibGP::slice_into(Eigen::VectorXi& A, std::vector<int>& idx, const int b)
{
	for (int i = 0; i < idx.size(); i++)
	{
		A[idx[i]] = b;
	}
}
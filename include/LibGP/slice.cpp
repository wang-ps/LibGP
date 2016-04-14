#include "slice.h"

namespace LibGP
{
	LIBGP_INLINE void slice(MatrixXf& B, VectorXb& flag, const MatrixXf& A)
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

	LIBGP_INLINE void slice_into(MatrixXf& A, VectorXb& flag, const MatrixXf& B)
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


	LIBGP_INLINE void slice(MatrixXf& B, std::vector<int>& idx, const MatrixXf& A)
	{
		B.resize(A.rows(), idx.size());
		for (int i = 0; i < idx.size(); i++)
		{
			B.col(i) = A.col(idx[i]);
		}
	}

	LIBGP_INLINE void slice_into(MatrixXf& A, std::vector<int>& idx, const MatrixXf& B)
	{
		for (int i = 0; i < idx.size(); i++)
		{
			A.col(idx[i]) = B.col(i);
		}
	}

	LIBGP_INLINE void slice_into(VectorXi& A, VectorXb& flag, const int b)
	{
		assert(A.rows() == flag.size());

		for (int i = 0; i < flag.size(); i++)
		{
			if (flag[i]) A[i] = b;
		}
	}

	LIBGP_INLINE void slice_into(VectorXi& A, std::vector<int>& idx, const int b)
	{
		for (int i = 0; i < idx.size(); i++)
		{
			A[idx[i]] = b;
		}
	}
}

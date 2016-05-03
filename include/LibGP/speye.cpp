#include "speye.h"

namespace LibGP
{
	LIBGP_INLINE void LibGP::speye(SMatrixf& smat,
		const int n, const Float v)
	{
		smat.resize(n, n);
		smat.reserve(VectorXi::Constant(n, 1));
		for(int i = 0; i < n; i++)
		{
			smat.insert(i, i) = v;
		}
		smat.makeCompressed();
	}
}

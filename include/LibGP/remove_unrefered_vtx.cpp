#include "read_mesh.h"
#include "write_mesh.h"
#include "remove_unrefered_vtx.h"

namespace LibGP
{
	LIBGP_INLINE int remove_unrefered_vtx(std::string filename)
	{
		MatrixXf V; MatrixXi F;
		read_mesh(filename, V, F);

		int nf = F.cols();
		int nv = V.cols();

		VectorXb valid_v = VectorXb::Constant(nv, false);
		for (int i = 0; i < nf; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				valid_v[F(j, i)] = true;
			}
		}

		int nv1 = 0;
		VectorXi vi = VectorXi::Constant(nv, -1);
		for (int i = 0; i < nv; ++i)
		{
			if (valid_v[i])
			{
				vi[i] = nv1++;
			}
		}
		
		int n = nv - nv1;
		if (n > 0)
		{
			for (int i = 0; i < nf; ++i)
			{
				F.col(i) << vi[F(0, i)], vi[F(1, i)], vi[F(2, i)];
			}

			for (int i = 0; i < nv; ++i)
			{
				if (valid_v[i])
				{
					V.col(vi[i]) = V.col(i);
				}
			}
			V.conservativeResize(3, nv1);
		}
		write_mesh(filename, V, F);
		return n;
	}
}
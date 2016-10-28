#include "bounding_sphere.h"
#include <Miniball.hpp>


namespace LibGP
{
	LIBGP_INLINE void bounding_sphere(
		VectorXf& center, Float& radius, const MatrixXf& V)
	{
		// mini ball interface
		int n = V.cols();
		int d = V.rows();

		const Float** ap = new const Float*[n];
		for (int i = 0; i < n; ++i)
		{
			ap[i] = V.col(i).data();
		}

		typedef const Float** PointIterator;
		typedef const Float* CoordIterator;
		Miniball::Miniball <
			Miniball::CoordAccessor < PointIterator, CoordIterator >>
			miniball(V.rows(), ap, ap + n);

		// get result
		center.resize(d);
		const Float* cnt = miniball.center();
		for (int i = 0; i < d; ++i)
		{
			center[i] = cnt[i];
		}
		radius = sqrt(miniball.squared_radius() + LibGP::EPS);
		
		cout << "Computation time was " << miniball.get_time() << " seconds\n";
		delete[] ap;
	}
}

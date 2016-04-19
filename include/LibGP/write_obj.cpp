#include "write_obj.h"

namespace LibGP{
	template <typename DerivedV, typename DerivedF>
	LIBGP_INLINE bool write_obj(std::string filename,
		const Eigen::MatrixBase<DerivedV>& V,
		const Eigen::MatrixBase<DerivedF>& F)
	{
		std::ofstream outfile(filename, std::ios::binary);
		if (!outfile)
		{
			cout << "Open OBJ file error!" << endl;
			return false;
		}

		// turn to string
		std::vector<char[128]> vec1(V.cols());
		#pragma omp parallel for 
		for (int i = 0; i < V.cols(); i++)
		{
			sprintf(vec1[i], "v %.6f %.6f %.6f\n", V(0, i), V(1, i), V(2, i));			
		}

		std::vector<char[128]> vec2(F.cols());
		#pragma omp parallel for 
		for (int i = 0; i < F.cols(); i++)
		{
			sprintf(vec2[i], "f %d %d %d\n", F(0, i) + 1, F(1, i) + 1, F(2, i) + 1);
		}

		// concat
		std::string str;
		for (int i = 0; i < V.cols(); str += vec1[i++]);
		for (int i = 0; i < F.cols(); str += vec2[i++]);

		// write into file
		outfile.write(str.data(), str.size());

		// close file
		outfile.close();
		return true;

		// 
		// 	// write into file
		// 	outfile.write(str.data(), str.size());

		// 	//std::setprecision(9)
		// 	outfile << std::fixed ;
		// 	for (int i = 0; i < V.cols(); i++)
		// 	{
		// 		outfile << "v " << V(0, i) << ' ' << V(1, i) << ' ' << V(2, i) << "\n";
		// 	}
		// 
		// 	for (int i = 0; i < F.cols(); i++)
		// 	{
		// 		outfile << "f " << F(0, i) + 1 << ' ' << F(1, i) + 1 << ' ' << F(2, i) + 1 << "\n";
		// 	}
	}
}

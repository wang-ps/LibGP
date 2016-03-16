#include <iostream>
#include <LibGP\read_obj.h>
#include <LibGP\write_obj.h>
#include <ctime>


int main()
{
	//freopen("C:\\Users\\v-pewan\\Desktop\\debug_output.txt", "w", stdout);

	//std::string filename = "C:\\Users\\v-pewan\\Desktop\\test.obj";
	std::string filename = "D:\\Paper\\RollingGuidanceNormalFilter\\data\\Geometry Texture Removal\\Gargoyle\\gargoyle.obj";
	std::string filename1 = "C:\\Users\\v-pewan\\Desktop\\gargoyle.obj";


	Eigen::MatrixXd V;
	Eigen::MatrixXi F;

	clock_t t1, t2; 
	t1 = clock();
	LibGP::read_obj(filename, V, F);
	t2 = clock();
	std::cout << t2 - t1 << std::endl;


	LibGP::write_obj(filename1, V, F);

// 	std::cout << V << std::endl << std::endl;
// 	std::cout << F << std::endl << std::endl;


	return 0;
}
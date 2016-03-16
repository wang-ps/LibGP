#include <iostream>
#include <LibGP\read_obj.h>
#include <LibGP\write_obj.h>
#include <LibGP\read_off.h>
#include <LibGP\write_off.h>
#include <ctime>
// openmesh
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
typedef OpenMesh::TriMesh_ArrayKernelT<>  Mesh;

int main()
{
	//freopen("C:\\Users\\v-pewan\\Desktop\\debug_output.txt", "w", stdout);

//	std::string filename = "C:\\Users\\v-pewan\\Desktop\\eight.off";
//	std::string filename = "D:\\Paper\\RollingGuidanceNormalFilter\\data\\Geometry Texture Removal\\Circular box\\circular_box.obj";
// 	std::string filename1 = "C:\\Users\\v-pewan\\Desktop\\gargoyle.obj";
// 
 	std::string filename2 = "D:\\Models\\armadillo.off";
  	std::string filename3 = "C:\\Users\\v-pewan\\Desktop\\eight.obj";
 	std::string filename4 = "C:\\Users\\v-pewan\\Desktop\\test.off";



	Eigen::MatrixXd V;
	Eigen::MatrixXi F;

 	clock_t t1, t2; 
// 	t1 = clock();
// 	LibGP::read_obj(filename, V, F);
// 	t2 = clock();
// 	std::cout << t2 - t1 << std::endl;

	t1 = clock();
	LibGP::read_off(filename4, V, F);
	t2 = clock();
	std::cout << t2 - t1 << std::endl;

// 	Mesh mesh;
// 	t1 = clock();
// 	OpenMesh::IO::read_mesh(mesh, filename);
// 	t2 = clock();
// 	std::cout << t2 - t1 << std::endl;

	t1 = clock();
	LibGP::write_obj(filename3, V, F);
	t2 = clock();
	std::cout << t2 - t1 << std::endl;

	t1 = clock();
	LibGP::write_off(filename2, V, F);
	t2 = clock();
	std::cout << t2 - t1 << std::endl;

// 	std::cout << V << std::endl << std::endl;
// 	std::cout << F << std::endl << std::endl;


	return 0;
}
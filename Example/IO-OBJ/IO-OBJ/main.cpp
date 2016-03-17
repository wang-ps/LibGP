#include <iostream>
#include <ctime>

// LibGP
#include <LibGP\read_mesh.h>
#include <LibGP\write_mesh.h>

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
 	std::string filename2 = "C:\\Users\\v-pewan\\Desktop\\circular_box_opt_mesh.obj";
  	std::string filename3 = "C:\\Users\\v-pewan\\Desktop\\circular_box_opt.obj";
 	std::string filename4 = "C:\\Users\\v-pewan\\Desktop\\circular_box.obj";
	
	Eigen::MatrixXd V;
	Eigen::MatrixXi F;

 	clock_t t1, t2; 
// 	t1 = clock();
// 	LibGP::read_obj(filename, V, F);
// 	t2 = clock();
// 	std::cout << t2 - t1 << std::endl;

	t1 = clock();
	LibGP::read_mesh(filename4, V, F);
	t2 = clock();
	std::cout << t2 - t1 << std::endl;

	Mesh mesh;
	t1 = clock();
	OpenMesh::IO::read_mesh(mesh, filename4);
	t2 = clock();
	std::cout << t2 - t1 << std::endl;

	t1 = clock();
	LibGP::write_mesh(filename2, V, F);
	t2 = clock();
	std::cout << t2 - t1 << std::endl;


	t1 = clock();
	OpenMesh::IO::write_mesh(mesh, filename3);
	t2 = clock();
	std::cout << t2 - t1 << std::endl;

// 	std::cout << V << std::endl << std::endl;
// 	std::cout << F << std::endl << std::endl;


	return 0;
}
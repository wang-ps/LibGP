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

  	std::string filename3 = "C:\\Users\\v-pewan\\Desktop\\circular_box_opt.obj";
	std::string filename1 = "D:\\Projects\\libigl\\external\\cork\\samples\\ballA.off";
	std::string filename2 = "D:\\Projects\\libigl\\external\\cork\\samples\\ballA-test.off";

	Eigen::MatrixXd V;
	Eigen::MatrixXi F;

 	clock_t t1, t2; 

	t1 = clock();
	LibGP::read_mesh(filename1, V, F);
	t2 = clock();
	std::cout << t2 - t1 << std::endl;
// 
// 	Mesh mesh;
// 	t1 = clock();
// 	OpenMesh::IO::read_mesh(mesh, filename4);
// 	t2 = clock();
// 	std::cout << t2 - t1 << std::endl;

	t1 = clock();
	LibGP::write_mesh(filename2, V, F);
	t2 = clock();
	std::cout << t2 - t1 << std::endl;


// 	t1 = clock();
// 	OpenMesh::IO::write_mesh(mesh, filename3);
// 	t2 = clock();
// 	std::cout << t2 - t1 << std::endl;

// 	std::cout << V << std::endl << std::endl;
// 	std::cout << F << std::endl << std::endl;


	return 0;
}
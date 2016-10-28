#include <iostream>
#include <string>
#include <LibGP/read_mesh.h>
#include <LibGP/bounding_sphere.h>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 2) return 0;
	LibGP::MatrixXf V; LibGP::MatrixXi F;
	string filename(argv[1]);
	LibGP::read_mesh(filename, V, F);
	
	LibGP::VectorXf center;
	LibGP::Float radius;
	LibGP::bounding_sphere(center, radius, V);
	cout << "Center:\n" << center << endl;
	cout << "Radius:\n" << radius << endl;
	return 0;
}
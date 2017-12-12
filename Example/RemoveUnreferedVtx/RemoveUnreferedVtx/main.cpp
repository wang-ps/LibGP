#include <iostream>
#include <vector>
#include <string>
#include <LibGP/remove_unrefered_vtx.h>
#include <LibGP/get_all_filenames.h>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		cout << "Usage: RemoveUnreferedVtx.exe "
			"<file path> [suffix]" << endl;
		return 0;
	}

	string path_name(argv[1]);
	string suffix(argv[2]);

	vector<string> filenames;
	LibGP::get_all_filenames(filenames, path_name + "\\*." + suffix);

	#pragma omp parallel for
	for (int i = 0; i < filenames.size(); i++)
	{
		LibGP::MatrixXf V;
		LibGP::MatrixXi F;
		LibGP::read_mesh(filenames[i], V, F);

		int n = LibGP::remove_unrefered_vtx(V, F);

		if (n > 0)
		{
			LibGP::write_mesh(filenames[i], V, F);
		}

		string msg = filenames[i].substr(filenames[i].rfind('\\') + 1) +
			": remove " + to_string(n) + " unreferenced vertices.\n";
		cout << msg;
	}

	return 0;
}


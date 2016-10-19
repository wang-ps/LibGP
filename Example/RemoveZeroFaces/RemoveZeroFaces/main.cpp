#include <iostream>
#include <vector>
#include <string>
#include <LibGP/read_mesh.h>
#include <LibGP/write_mesh.h>
#include <LibGP/delete_faces.h>
#include <LibGP/compute_face_normal.h>
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

		LibGP::MatrixXf N;
		LibGP::VectorXf f_area;
		LibGP::compute_face_normal(N, f_area, V, F);

		int nf = F.cols();
		int k = 0;
		LibGP::VectorXb valid_f = LibGP::VectorXb::Constant(nf, true);
		for (int j = 0; j < nf; ++j)
		{
			if (f_area[j] < 1.0e-20)
			{
				valid_f[j] = false;
				k++;
			}
		}
		if (k > 0)
		{
			LibGP::delete_faces(V, F, valid_f);
			LibGP::write_mesh(filenames[i], V, F);
		}

		string msg = filenames[i].substr(filenames[i].rfind('\\') + 1) +
			": remove " + to_string(k) + " degenarated faces.\n";
		cout << msg;
	}

	return 0;
}


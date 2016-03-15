#include <LibGP\get_filename.h>
#include <LibGP\get_all_filenames.h>
#include <vector>
#include <iostream>
using namespace std;

int main()
{
	string filename;
	LibGP::get_filename(filename, true, LibGP::MODEL_FILE);
	cout << filename << endl << endl;

	vector<string> vec_names;
	LibGP::get_all_filenames(vec_names, filename);
	for (int i = 0; i < vec_names.size(); i++)
	{
		cout << vec_names[i] << endl;
	}
	
	return 0;
}
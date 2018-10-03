#include "write_obj.h"

namespace LibGP {

LIBGP_INLINE bool write_obj(std::string filename, const MatrixXf& V, const MatrixXi& F) {
  std::ofstream outfile(filename, std::ios::binary);
  if (!outfile) {
    cout << "Open OBJ file error!" << endl;
    return false;
  }

  // buffer
  const int len = 64;
  char* buffer = new char[(V.cols() + F.cols())*len];

  // turn to string
  char* pV = buffer;
  #pragma omp parallel for
  for (int i = 0; i < V.cols(); i++) {
    sprintf(pV + i * len, "v %.6f %.6f %.6f\n", V(0, i), V(1, i), V(2, i));
  }

  char* pF = buffer + V.cols() * len;
  #pragma omp parallel for
  for (int i = 0; i < F.cols(); i++) {
    sprintf(pF + i * len, "f %d %d %d\n", F(0, i) + 1, F(1, i) + 1, F(2, i) + 1);
  }

  int k = 0;
  for (int i = 0; i < V.cols(); i++) {
    for (int j = len * i; j < len * (i + 1); j++) {
      if (pV[j] == 0) break;
      buffer[k++] = pV[j];
    }
  }
  for (int i = 0; i < F.cols(); i++) {
    for (int j = len * i; j < len * (i + 1); j++) {
      if (pF[j] == 0) break;
      buffer[k++] = pF[j];
    }
  }

  // write into file
  outfile.write(buffer, k);

  // close file
  outfile.close();
  delete[] buffer;
  return true;
}

}  // namespace LibGP

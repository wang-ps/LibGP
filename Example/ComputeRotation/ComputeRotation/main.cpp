#include <iostream>
using namespace std;

// row major
void compute_rotation(float* rot, const float* axis, const float cosa) {
  float cosa1 = 1 - cosa;
  float sina = sqrtf(1 - cosa * cosa);
  float xx = axis[0] * axis[0];
  float xy = axis[0] * axis[1];
  float xz = axis[0] * axis[2];
  float yy = axis[1] * axis[1];
  float yz = axis[1] * axis[2];
  float zz = axis[2] * axis[2];
  float xyc = xy * cosa1;
  float xzc = xz * cosa1;
  float yzc = yz * cosa1;
  float xs = axis[0] * sina;
  float ys = axis[1] * sina;
  float zs = axis[2] * sina;

  rot[0] = cosa + xx * cosa1;
  rot[1] = xyc - zs;
  rot[2] = xzc + ys;
  rot[3] = xyc + zs;
  rot[4] = cosa + yy * cosa1;
  rot[5] = yzc - xs;
  rot[6] = xzc - ys;
  rot[7] = yzc + xs;
  rot[8] = cosa + zz * cosa1;
}

void rotate_vec3f(float* vout, const float* rot, const float* vin) {
  vout[0] = rot[0] * vin[0] + rot[1] * vin[1] + rot[2] * vin[2];
  vout[1] = rot[3] * vin[0] + rot[4] * vin[1] + rot[5] * vin[2];
  vout[2] = rot[6] * vin[0] + rot[7] * vin[1] + rot[8] * vin[2];
}

int main() {

  float axis[3] = { 1.0f, 2.0f, 3.0f };
  for (int c = 0; c < 3; ++c) axis[c] /= sqrtf(14.0f);
  float cosa = cos(1.0f);
  float rot[9] = { 0 };
  compute_rotation(rot, axis, cosa);
  for (int i = 0; i < 9; ++i) {
    cout << rot[i] << "\t";
    if ((i + 1) % 3 == 0) cout << endl;
  }
  cout << endl;

  return 0;
}
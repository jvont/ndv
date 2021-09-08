#include <ndv/vec.h>
#include <ndv/mat.h>
// #include <ndv/quat.h>
using namespace ndv;

#include <iostream>

int main()
{
  // Mat<2, 2, float> m2({
  //   {1, 2},
  //   {4, 3}
  // });
  // Mat<2, 2, float> trans2 = transpose(m2);
  // Mat<2, 2, float> det2 = determinant(m2);
  // Mat<2, 2, float> cof2 = cofactor(m2);

  Mat<3, 3, float> m3({
    {0, 9, 3},
    {2, 0, 4},
    {3, 7, 0}
  });
  // Vec<3, float> v3({2, 1, 2});
  // Vec<3, float> mv3 = m3 * v3;
  // Mat<2, 2, float> sub3 = submatrix(m3, 1, 2);
  // Mat<3, 3, float> cof3 = cofactor(m3);
  // float det3 = determinant(m3);

  // Mat<4, 4, float> m4({
  //   {0, 9, 3, 4},
  //   {2, 0, 4, 8},
  //   {3, 7, 0, 1},
  //   {2, 2, 3, 4}
  // });
  // Mat<4, 4, float> inv4 = inverse(m4);
  // float det4 = determinant(m4);

  // Mat<3, 3, float> m = scale(Vec<2, float>(1, 2), m3);
  // Mat<4, 4, float> m = rotate(Vec<3, float>(0, 1, 1), 0.15f);

  scale(m3, Vec<2, float>(1, 2));

  Mat<3, 3, float> m4({
    {0, 9, 3},
    {2, 0, 4},
    {3, 7, 0}
  });
  scale(m4, Vec<3, float>(1, 2, 3));

  return 0;
}
#include <ndv/vec.h>
#include <ndv/mat.h>
#include <ndv/quat.h>
using namespace ndv;

#include <iostream>

int main()
{

  Mat<2, 2, float> m({
    {1, 2},
    {4, 3}
  });
  Mat<2, 2, float> r = transpose(m);

  return 0;
}
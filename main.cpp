#include <ndv/vec.h>
#include <ndv/mat.h>
using namespace bones;

#include <iostream>

int main()
{

  Mat<2, 2, float> m1( {0, 1, 2, 3} );
  Mat<2, 2, float> m2( {{0, 1}, {2, 3}} );

  return 0;
}
#include <ndv/vec.h>

#include <iostream>
#include <array>

int main()
{
  Vec<2, int> v1(3, 3);
  Vec<2, int> v2(1, 2);

  v1 += v2;
  std::cout << "v1: " << v1[0] << ", " << v1[1] << std::endl;
  std::cout << "v2: " << v2[0] << ", " << v2[1] << std::endl;

  v1 -= v2;
  std::cout << "v1: " << v1[0] << ", " << v1[1] << std::endl;
  std::cout << "v2: " << v2[0] << ", " << v2[1] << std::endl;

  return 0;
}
#include <ndv/vec.h>

#include <iostream>

int main()
{
  Vec<2, int> v1;
  Vec<2, int> v2;

  v1.values[0] = 5;
  v1.values[1] = 6;
  v2.values[0] = 1;
  v2.values[1] = 1;

  std::cout << v1.values[0] << ", " << v1.values[1] << " + " 
            << v2.values[0] << ", " << v2.values[1] << std::endl;

  v1 += v2;

  std::cout << v1.values[0] << ", " << v1.values[1] << " + " 
            << v2.values[0] << ", " << v2.values[1] << std::endl;

  return 0;
}
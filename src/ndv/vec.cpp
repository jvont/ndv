#include <ndv/vec.h>

template<int N, typename T>
Vec<N, T>& Vec<N, T>::operator+=(const Vec<N, T>& v)
{
  for (int i=0; i<N; i++)
  {
    values[i] += v.values[i];
  }
}

template<int N, typename T>
Vec<N, T> operator*(const Vec<N, T>& v1, const Vec<N, T>& v2)
{
  Vec<N, T> result;
  for (int i=0; i<N; i++)
  {
    result.values[i] = v1.values[i] * v2.values[i];
  }
}

template<int N, typename T>
Vec<N, T> operator*(const Vec<N, T>& v, float s)
{
  Vec<N, T> result;
  for (int i=0; i<N; i++)
  {
    result.values[i] = v.values[i] * s;
  }
}


template struct Vec<2, int>;

using Vec2i = Vec<2, int>;

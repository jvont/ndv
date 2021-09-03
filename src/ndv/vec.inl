template<int N, typename T>
Vec<N, T>::Vec() : values{static_cast<T>(0)} {}

template<int N, typename T>
Vec<N, T>::Vec(T s)
{
  for (int i=0; i<N; i++)
  {
    values[i] = s;
  }
}

template<int N, typename T>
str Vec<N, T>::to_string() const
{
  str result = "{ ";
  for (int i=0; i<N-1; i++)
  {
    result += std::to_string(values[i]);
    result += ", ";
  }
  result += std::to_string(values[N-1]);
  result += " }";
  return result;
};

template<int N, typename T>
T Vec<N, T>::operator[](int i) const
{
  assert(i >= 0 && i < N);
  return values[i];
}

template<int N, typename T>
T& Vec<N, T>::operator[](int i)
{
  assert(i >= 0 && i < N);
  return values[i];
}

template<int N, typename T>
Vec<N, T>& Vec<N, T>::operator=(const Vec<N, T>& v)
{
  for (int i=0; i<N; i++)
  {
    values[i] = v.values[i];
  }
  return *this;
}

template<int N, typename T>
Vec<N, T>& Vec<N, T>::operator+=(const Vec<N, T>& v)
{
  for (int i=0; i<N; i++)
  {
    values[i] += v.values[i];
  }
  return *this;
}

template<int N, typename T>
Vec<N, T>& Vec<N, T>::operator-=(const Vec<N, T>& v)
{
  for (int i=0; i<N; i++)
  {
    values[i] -= v.values[i];
  }
  return *this;
}

template<int N, typename T>
Vec<N, T>& Vec<N, T>::operator*=(const Vec<N, T>& v)
{
  for (int i=0; i<N; i++)
  {
    values[i] *= v.values[i];
  }
  return *this;
}

template<int N, typename T>
Vec<N, T>& Vec<N, T>::operator*=(T s)
{
  for (int i=0; i<N; i++)
  {
    values[i] *= s;
  }
  return *this;
}

template<int N, typename T>
Vec<N, T>& Vec<N, T>::operator/=(const Vec<N, T>& v)
{
  for (int i=0; i<N; i++)
  {
    values[i] /= v.values[i];
  }
  return *this;
}

template<int N, typename T>
Vec<N, T>& Vec<N, T>::operator/=(T s)
{
  for (int i=0; i<N; i++)
  {
    values[i] /= s;
  }
  return *this;
}

template<int N, typename T>
Vec<N, T> operator+(const Vec<N, T>& v)
{
  return v;
}

template<int N, typename T>
Vec<N, T> operator-(const Vec<N, T>& v)
{
  Vec<N, T> result;
  for (int i=0; i<N; i++)
  {
    result.values[i] = -v.values[i];
  }
  return result;
}

template<int N, typename T>
Vec<N, T> operator+(const Vec<N, T>& v1, const Vec<N, T>& v2)
{
  Vec<N, T> result;
  for (int i=0; i<N; i++)
  {
    result.values[i] = v1.values[i] + v2.values[i];
  }
  return result;
}

template<int N, typename T>
Vec<N, T> operator-(const Vec<N, T>& v1, const Vec<N, T>& v2)
{
  Vec<N, T> result;
  for (int i=0; i<N; i++)
  {
    result.values[i] = v1.values[i] - v2.values[i];
  }
  return result;
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
Vec<N, T> operator*(const Vec<N, T>& v, T s)
{
  Vec<N, T> result;
  for (int i=0; i<N; i++)
  {
    result.values[i] = v.values[i] * s;
  }
}

template<int N, typename T>
Vec<N, T> operator*(T s, const Vec<N, T>& v)
{
  Vec<N, T> result;
  for (int i=0; i<N; i++)
  {
    result.values[i] = s * v.values[i];
  }
}

template<int N, typename T>
Vec<N, T> operator/(const Vec<N, T>& v1, const Vec<N, T>& v2)
{
  Vec<N, T> result;
  for (int i=0; i<N; i++)
  {
    result.values[i] = v1.values[i] / v2.values[i];
  }
  return result;
}

template<int N, typename T>
Vec<N, T> operator/(const Vec<N, T>& v, T s)
{
  Vec<N, T> result;
  for (int i=0; i<N; i++)
  {
    result.values[i] = v.values[i] / s;
  }
  return result;
}

template<int N, typename T>
Vec<N, T> operator/(T s, const Vec<N, T>& v)

{
  Vec<N, T> result;
  for (int i=0; i<N; i++)
  {
    result.values[i] = s / v.values[i];
  }
  return result;
}

template<int N, typename T>
bool operator==(const Vec<N, T>& v1, const Vec<N, T>& v2)
{
  for (int i=0; i<N; i++)
  {
    if (v1.values[i] != v2.values[i])
      return false;
  }
  return true;
}

template<int N, typename T>
bool operator!=(const Vec<N, T>& v1, const Vec<N, T>& v2)
{
  for (int i=0; i<N; i++)
  {
    if (v1.values[i] != v2.values[i])
      return true;
  }
  return false;
}

template<int N, typename T>
bool operator<(const Vec<N, T>& v1, const Vec<N, T>& v2)
{
  for (int i=0; i<N; i++)
  {
    if (v1.values[i] < v2.values[i])
      return true;
    else if (v1.values[i] > v2.values[i])
      return false;
    // else equal, check next
  }
  return false; // all equal
}

template<int N, typename T>
bool operator>(const Vec<N, T>& v1, const Vec<N, T>& v2)
{
  for (int i=0; i<N; i++)
  {
    if (v1.values[i] > v2.values[i])
      return true;
    else if (v1.values[i] < v2.values[i])
      return false;
    // else equal, check next
  }
  return false; // all equal
}

template<int N, typename T>
bool operator<=(const Vec<N, T>& v1, const Vec<N, T>& v2)
{
  for (int i=0; i<N; i++)
  {
    if (v1.values[i] < v2.values[i])
      return true;
    else if (v1.values[i] > v2.values[i])
      return false;
    // else equal, check next
  }
  return true; // all equal
}

template<int N, typename T>
bool operator>=(const Vec<N, T>& v1, const Vec<N, T>& v2)
{
  for (int i=0; i<N; i++)
  {
    if (v1.values[i] > v2.values[i])
      return true;
    else if (v1.values[i] < v2.values[i])
      return false;
    // else equal, check next
  }
  return true; // all equal
}
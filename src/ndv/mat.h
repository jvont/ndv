#pragma once

#include <ndv/vec.h>

#include <assert.h>
#include <initializer_list>

namespace ndv
{
#pragma region "Mat Definitions"

  // Matrices are stored in column-major format. However, NxM denotes N rows
  // and M columns. Essentially, matrices are constructed in row-major format,
  // but the underlying structure is column-major.
  template<int N, int M, typename T>
  struct Mat
  {
    union
    {
      Vec<N, T> col[M];
      T data[M][N];
    };

    Mat();
    Mat(const std::initializer_list<T> args);
    Mat(const std::initializer_list<std::initializer_list<T>> args);

    Vec<N, T> operator[](int i) const;
    Vec<N, T>& operator[](int i);

    Mat& operator=(const Mat& rhs);
    Mat& operator+=(const Mat& rhs);
    Mat& operator-=(const Mat& rhs);
    Mat& operator*=(const Mat& rhs);
  };

  template<typename T>
  struct Mat<2, 2, T>
  {
    union
    {
      Vec<2, T> col[2];
      T data[2][2];
    };

    static const Mat identity;
    static const Mat zero;

    Mat();
    Mat(const std::initializer_list<T> args);
    Mat(const std::initializer_list<std::initializer_list<T>> args);

    Vec<2, T> operator[](int i) const;
    Vec<2, T>& operator[](int i);

    Mat& operator=(const Mat& rhs);
    Mat& operator+=(const Mat& rhs);
    Mat& operator-=(const Mat& rhs);
    Mat& operator*=(const Mat& rhs);
  };
  using Mat2x2i = Mat<2, 2, int>;
  using Mat2x2f = Mat<2, 2, float>;
  using Mat2x2d = Mat<2, 2, double>;

  template<typename T>
  struct Mat<3, 3, T>
  {
    union
    {
      Vec<3, T> col[3];
      T data[3][3];
    };

    static const Mat identity;
    static const Mat zero;

    Mat();
    Mat(const std::initializer_list<T> args);
    Mat(const std::initializer_list<std::initializer_list<T>> args);

    Vec<3, T> operator[](int i) const;
    Vec<3, T>& operator[](int i);

    Mat& operator=(const Mat& rhs);
    Mat& operator+=(const Mat& rhs);
    Mat& operator-=(const Mat& rhs);
    Mat& operator*=(const Mat& rhs);
  };
  using Mat3x3i = Mat<3, 3, int>;
  using Mat3x3f = Mat<3, 3, float>;
  using Mat3x3d = Mat<3, 3, double>;

  template<typename T>
  struct Mat<4, 4, T>
  {
    union
    {
      Vec<4, T> col[4];
      T data[4][4];
    };

    static const Mat identity;
    static const Mat zero;

    Mat();
    Mat(const std::initializer_list<T> args);
    Mat(const std::initializer_list<std::initializer_list<T>> args);

    Vec<4, T> operator[](int i) const;
    Vec<4, T>& operator[](int i);

    Mat& operator=(const Mat& rhs);
    Mat& operator+=(const Mat& rhs);
    Mat& operator-=(const Mat& rhs);
    Mat& operator*=(const Mat& rhs);
  };
  using Mat4x4i = Mat<4, 4, int>;
  using Mat4x4f = Mat<4, 4, float>;
  using Mat4x4d = Mat<4, 4, double>;

#pragma endregion
#pragma region "Base Methods"
  template<int N, int M, typename T>
  inline Mat<N, M, T>::Mat()
  {
    for (int c = 0; c < M; c++)
      for (int r = 0; r < N; r++)
        data[c][r] = (c == r) ? T(1) : T(0);
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T>::Mat(const std::initializer_list<T> args)
  {
    assert(args.size() <= N * M);
    int c = 0, r = 0;
    for (auto it = args.begin(); it != args.end(); ++it)
    {
      data[c][r++] = *it;
      if (r >= N)
      {
        c++;
        r = 0;
      }
    }
  }
  
  template<int N, int M, typename T>
  inline Mat<N, M, T>::Mat(const std::initializer_list<std::initializer_list<T>> args)
  {
    assert(args.size() <= N);
    int r = 0;
    for (auto it1 = args.begin(); it1 != args.end(); ++it1)
    {
      std::initializer_list<T> args2 = *it1;
      assert(args2.size() <= M);
      int c = 0;
      for (auto it2 = args2.begin(); it2 != args2.end(); ++it2)
      {
        data[c++][r] = *it2;
      }
      r++;
    }
  }

  template<int N, int M, typename T>
  inline Vec<N, T> Mat<N, M, T>::operator[](int i) const
  {
    assert(i >= 0 && i < M);
    return col[i];
  }

  template<int N, int M, typename T>
  inline Vec<N, T>& Mat<N, M, T>::operator[](int i)
  {
    assert(i >= 0 && i < M);
    return col[i];
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T>& Mat<N, M, T>::operator=(const Mat<N, M, T>& rhs)
  {
    for (int c = 0; c < M; c++)
      data[c] = rhs[c];
    return *this;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T>& Mat<N, M, T>::operator+=(const Mat<N, M, T>& rhs)
  {
    for (int c = 0; c < M; c++)
      for (int r = 0; r < N; r++)
        data[c][r] += rhs[c][r]
    return *this;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T>& Mat<N, M, T>::operator-=(const Mat<N, M, T>& rhs)
  {
    for (int c = 0; c < M; c++)
      for (int r = 0; r < N; r++)
        data[c][r] -= rhs[c][r]
    return *this;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T>& Mat<N, M, T>::operator*=(const Mat<N, M, T>& rhs)
  {
    *this = *this * rhs;
    return *this;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T> operator+(const Mat<N, M, T>& rhs)
  {
    return rhs;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T> operator-(const Mat<N, M, T>& rhs)
  {
    Mat<N, M, T> result;
    for (int c = 0; c < M; c++)
      for (int r = 0; r < N; r++)
        result[c][r] = -rhs[c][r]
    return result;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T> operator+(const Mat<N, M, T>& lhs, const Mat<N, M, T>& rhs)
  {
    Mat<N, M, T> result;
    for (int c = 0; c < M; c++)
      for (int r = 0; r < N; r++)
        result[c][r] = lhs[c][r] + rhs[c][r]
    return result;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T> operator-(const Mat<N, M, T>& lhs, const Mat<N, M, T>& rhs)
  {
    Mat<N, M, T> result;
    for (int c = 0; c < M; c++)
      for (int r = 0; r < N; r++)
        result[c][r] = lhs[c][r] - rhs[c][r]
    return result;
  }

  template<int N, int M, int O, typename T>
  inline Mat<N, O, T> operator*(const Mat<N, M, T>& lhs, const Mat<M, O, T>& rhs)
  {
    Mat<N, O, T> result;
    for (int c = 0; c < O; c++)
    {
      for (int r = 0; r < N; r++)
      {
        T val = 0;
        for (int i = 0; i < M; i++)
          val += lhs[i][r] * rhs[c][i];
        result[c][r] = val;
      }
    }
    return result;
  }

  template<int N, int M, typename T>
  inline Vec<N, T> operator*(const Mat<N, M, T>& lhs, const Vec<M, T>& rhs)
  {
    Vec<N, T> result;
    for (int r = 0; r < N; r++)
    {
      T val = 0;
      for (int c = 0; c < M; c++)
        val += lhs[c][r] * rhs[c];
      result[r] = val;
    }
    return result;
  }

  template<int N, int M, typename T>
  inline bool operator==(const Mat<N, M, T>& lhs, const Mat<N, M, T>& rhs)
  {
    for (int c = 0; c < M; c++)
      for (int r = 0; r < N; r++)
        if (lhs[c][r] != rhs[c][r])
          return false;
    return true;
  }

  template<int N, int M, typename T>
  inline bool operator!=(const Mat<N, M, T>& lhs, const Mat<N, M, T>& rhs)
  {
    for (int c = 0; c < M; c++)
      for (int r = 0; r < N; r++)
        if (lhs[c][r] != rhs[c][r])
          return true;
    return false;
  }

#pragma endregion
#pragma region "Mat2 Methods"
  template<typename T>
  inline Mat<2, 2, T>::Mat()
  {
    for (int c = 0; c < 2; c++)
      for (int r = 0; r < 2; r++)
        data[c][r] = (c == r) ? T(1) : T(0);
  }

  template<typename T>
  inline Mat<2, 2, T>::Mat(const std::initializer_list<T> args)
  {
    assert(args.size() <= 4);
    int c = 0, r = 0;
    for (auto it = args.begin(); it != args.end(); ++it)
    {
      data[c][r++] = *it;
      if (r >= 2)
      {
        c++;
        r = 0;
      }
    }
  }
  
  template<typename T>
  inline Mat<2, 2, T>::Mat(const std::initializer_list<std::initializer_list<T>> args)
  {
    assert(args.size() <= 2);
    int r = 0;
    for (auto it1 = args.begin(); it1 != args.end(); ++it1)
    {
      std::initializer_list<T> args2 = *it1;
      assert(args2.size() <= 2);
      int c = 0;
      for (auto it2 = args2.begin(); it2 != args2.end(); ++it2)
      {
        data[c++][r] = *it2;
      }
      r++;
    }
  }

  template<typename T> const Mat<2, 2, T> Mat<2, 2, T>::identity = Mat<2, 2, T>({{1,0},{0,1}});
  template<typename T> const Mat<2, 2, T> Mat<2, 2, T>::zero = Mat<2, 2, T>({{0,0},{0,0}});

  template<typename T>
  inline Vec<2, T> Mat<2, 2, T>::operator[](int i) const
  {
    assert(i >= 0 && i < 2);
    return col[i];
  }

  template<typename T>
  inline Vec<2, T>& Mat<2, 2, T>::operator[](int i)
  {
    assert(i >= 0 && i < 2);
    return col[i];
  }

  template<typename T>
  inline Mat<2, 2, T>& Mat<2, 2, T>::operator=(const Mat<2, 2, T>& rhs)
  {
    for (int c = 0; c < 2; c++)
      data[c] = rhs[c];
    return *this;
  }

  template<typename T>
  inline Mat<2, 2, T>& Mat<2, 2, T>::operator+=(const Mat<2, 2, T>& rhs)
  {
    for (int c = 0; c < 2; c++)
      for (int r = 0; r < 2; r++)
        data[c][r] += rhs[c][r]
    return *this;
  }

  template<typename T>
  inline Mat<2, 2, T>& Mat<2, 2, T>::operator-=(const Mat<2, 2, T>& rhs)
  {
    for (int c = 0; c < 2; c++)
      for (int r = 0; r < 2; r++)
        data[c][r] -= rhs[c][r]
    return *this;
  }

  template<typename T>
  inline Mat<2, 2, T>& Mat<2, 2, T>::operator*=(const Mat<2, 2, T>& rhs)
  {
    *this = *this * rhs;
    return *this;
  }

#pragma endregion
#pragma region "Mat3 Methods"
  template<typename T>
  inline Mat<3, 3, T>::Mat()
  {
    for (int c = 0; c < 3; c++)
      for (int r = 0; r < 3; r++)
        data[c][r] = (c == r) ? T(1) : T(0);
  }

  template<typename T>
  inline Mat<3, 3, T>::Mat(const std::initializer_list<T> args)
  {
    assert(args.size() <= 9);
    int c = 0, r = 0;
    for (auto it = args.begin(); it != args.end(); ++it)
    {
      data[c][r++] = *it;
      if (r >= 3)
      {
        c++;
        r = 0;
      }
    }
  }
  
  template<typename T>
  inline Mat<3, 3, T>::Mat(const std::initializer_list<std::initializer_list<T>> args)
  {
    assert(args.size() <= 3);
    int r = 0;
    for (auto it1 = args.begin(); it1 != args.end(); ++it1)
    {
      std::initializer_list<T> args2 = *it1;
      assert(args2.size() <= 3);
      int c = 0;
      for (auto it2 = args2.begin(); it2 != args2.end(); ++it2)
      {
        data[c++][r] = *it2;
      }
      r++;
    }
  }

  template<typename T> const Mat<3, 3, T> Mat<3, 3, T>::identity = Mat<3, 3, T>({{1,0,0},{0,1,0},{0,0,1}});
  template<typename T> const Mat<3, 3, T> Mat<3, 3, T>::zero = Mat<3, 3, T>({{0,0,0},{0,0,0},{0,0,0}});

  template<typename T>
  inline Vec<3, T> Mat<3, 3, T>::operator[](int i) const
  {
    assert(i >= 0 && i < 3);
    return col[i];
  }

  template<typename T>
  inline Vec<3, T>& Mat<3, 3, T>::operator[](int i)
  {
    assert(i >= 0 && i < 3);
    return col[i];
  }

  template<typename T>
  inline Mat<3, 3, T>& Mat<3, 3, T>::operator=(const Mat<3, 3, T>& rhs)
  {
    for (int c = 0; c < 3; c++)
      data[c] = rhs[c];
    return *this;
  }

  template<typename T>
  inline Mat<3, 3, T>& Mat<3, 3, T>::operator+=(const Mat<3, 3, T>& rhs)
  {
    for (int c = 0; c < 3; c++)
      for (int r = 0; r < 3; r++)
        data[c][r] += rhs[c][r]
    return *this;
  }

  template<typename T>
  inline Mat<3, 3, T>& Mat<3, 3, T>::operator-=(const Mat<3, 3, T>& rhs)
  {
    for (int c = 0; c < 3; c++)
      for (int r = 0; r < 3; r++)
        data[c][r] -= rhs[c][r]
    return *this;
  }

  template<typename T>
  inline Mat<3, 3, T>& Mat<3, 3, T>::operator*=(const Mat<3, 3, T>& rhs)
  {
    *this = *this * rhs;
    return *this;
  }

#pragma endregion
#pragma region "Mat4 Methods"
  template<typename T>
  inline Mat<4, 4, T>::Mat()
  {
    for (int c = 0; c < 4; c++)
      for (int r = 0; r < 4; r++)
        data[c][r] = (c == r) ? T(1) : T(0);
  }

  template<typename T>
  inline Mat<4, 4, T>::Mat(const std::initializer_list<T> args)
  {
    assert(args.size() <= 16);
    int c = 0, r = 0;
    for (auto it = args.begin(); it != args.end(); ++it)
    {
      data[c][r++] = *it;
      if (r >= 4)
      {
        c++;
        r = 0;
      }
    }
  }
  
  template<typename T>
  inline Mat<4, 4, T>::Mat(const std::initializer_list<std::initializer_list<T>> args)
  {
    assert(args.size() <= 4);
    int r = 0;
    for (auto it1 = args.begin(); it1 != args.end(); ++it1)
    {
      std::initializer_list<T> args2 = *it1;
      assert(args2.size() <= 4);
      int c = 0;
      for (auto it2 = args2.begin(); it2 != args2.end(); ++it2)
      {
        data[c++][r] = *it2;
      }
      r++;
    }
  }

  template<typename T> const Mat<4, 4, T> Mat<4, 4, T>::identity = Mat<4, 4, T>({{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}});
  template<typename T> const Mat<4, 4, T> Mat<4, 4, T>::zero = Mat<4, 4, T>({{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}});

  template<typename T>
  inline Vec<4, T> Mat<4, 4, T>::operator[](int i) const
  {
    assert(i >= 0 && i < 4);
    return col[i];
  }

  template<typename T>
  inline Vec<4, T>& Mat<4, 4, T>::operator[](int i)
  {
    assert(i >= 0 && i < 4);
    return col[i];
  }

  template<typename T>
  inline Mat<4, 4, T>& Mat<4, 4, T>::operator=(const Mat<4, 4, T>& rhs)
  {
    for (int c = 0; c < 4; c++)
      data[c] = rhs[c];
    return *this;
  }

  template<typename T>
  inline Mat<4, 4, T>& Mat<4, 4, T>::operator+=(const Mat<4, 4, T>& rhs)
  {
    for (int c = 0; c < 4; c++)
      for (int r = 0; r < 4; r++)
        data[c][r] += rhs[c][r]
    return *this;
  }

  template<typename T>
  inline Mat<4, 4, T>& Mat<4, 4, T>::operator-=(const Mat<4, 4, T>& rhs)
  {
    for (int c = 0; c < 4; c++)
      for (int r = 0; r < 4; r++)
        data[c][r] -= rhs[c][r]
    return *this;
  }

  template<typename T>
  inline Mat<4, 4, T>& Mat<4, 4, T>::operator*=(const Mat<4, 4, T>& rhs)
  {
    *this = *this * rhs;
    return *this;
  }

#pragma endregion
#pragma region "Utility Methods"

  // Mat2 Mat2::transpose() const
  // {
  //   return Mat2{{
  //     {row[0][0], row[1][0]},
  //     {row[0][1], row[1][1]}
  //   }};
  // }

  // real_t Mat2::determinant() const
  // {
  //   return (row[0][0] * row[1][1] - row[0][1] * row[1][0]);
  // }

  // Mat2 Mat2::cofactor() const
  // {
  //   return Mat2{{
  //     {row[1][1], -row[1][0]}, 
  //     {-row[0][1], row[0][0]}
  //   }};
  // }

  // Mat2 Mat2::adjoint() const
  // {
  //   return cofactor().transpose();
  // }

  // Mat2 Mat2::inverse() const
  // {
  //   real_t det = determinant();

  //   if (approx_equal(det, 0.0f))
  //     return Mat2::zero;

  //   return (adjoint() / det);
  // }

  // ========================================================================

  // Mat3 Mat3::transpose() const
  // {
  //   return Mat3{{
  //     {row[0][0], row[1][0], row[2][0]},
  //     {row[0][1], row[1][1], row[2][1]},
  //     {row[0][2], row[1][2], row[2][2]}
  //   }};
  // }

  // real_t Mat3::determinant() const
  // {
  //   return (
  //     row[0][0] * (row[1][1] * row[2][2] - row[1][2] * row[2][1]) - 
  //     row[1][0] * (row[0][1] * row[2][2] - row[0][2] * row[2][1]) + 
  //     row[2][0] * (row[0][1] * row[1][2] - row[0][2] * row[1][1])
  //   );
  // }

  // Mat3 Mat3::cofactor() const
  // {
  //   Mat3 result;
  //   for (int i = 0; i <  3; i++)
  //   {
  //     for (int j = 0; j < 3; j++)
  //     {
  //       // Mat2 m_ij(
  //       //   row[(i + 1) % 3][(j + 1) % 3], row[(i + 1) % 3][(j + 2) % 3],
  //       //   row[(i + 2) % 3][(j + 1) % 3], row[(i + 2) % 3][(j + 2) % 3]
  //       // );
  //       // result[i][j] = m_ij.determinant();

  //       real_t det_ij = (
  //         row[(i + 1) % 3][(j + 1) % 3] * row[(i + 2) % 3][(j + 2) % 3] - 
  //         row[(i + 1) % 3][(j + 2) % 3] * row[(i + 2) % 3][(j + 1) % 3]
  //       );
  //       result[i][j] = det_ij;
  //     }
  //   }
  //   return result;
  // }

  // Mat3 Mat3::adjoint() const
  // {
  //   return cofactor().transpose();
  // }

  // Mat3 Mat3::inverse() const
  // {
  //   real_t det = determinant();

  //   if (approx_equal(det, 0.0f))
  //     return Mat3::zero;

  //   return (adjoint() / det);
  // }

  // bool Mat3::is_affine() const
  // {
  //   return (
  //     row[0][2] == 0 &&
  //     row[1][2] == 0 &&
  //     row[2][2] == 1
  //   );
  // }

  // Mat3 scale(const Mat3& m, Vec2 scaling)
  // {
  //   return Mat3{{
  //     m[0] * scaling[0],
  //     m[1] * scaling[1],
  //     m[2]
  //   }};
  // }

  // Mat3 scale(Vec2 scaling)
  // {
  //   return scale(Mat3::identity, scaling);
  // }

  // Mat3 rotate(const Mat3& m, real_t angle)
  // {
  //   const real_t c = cos(angle);
  //   const real_t s = sin(angle);

  //   return Mat3{{
  //     m[0] * c + m[1] * s,
  //     m[0] * -s + m[1] * c,
  //     m[2]
  //   }};
  // }

  // Mat3 rotate(real_t angle)
  // {
  //   return rotate(Mat3::identity, angle);
  // }

  // Mat3 translate(const Mat3& m, Vec2 distance)
  // {
  //   return Mat3{{
  //     m[0],
  //     m[1],
  //     m[0] * distance[0] + m[1] * distance[1]  + m[2]
  //   }};
  // }

  // Mat3 translate(Vec2 distance)
  // {
  //   return translate(Mat3::identity, distance);
  // }

  // ========================================================================

  // Mat4 Mat4::transpose() const
  // {
  //   return Mat4{{
  //     {row[0][0], row[1][0], row[2][0], row[3][0]},
  //     {row[0][1], row[1][1], row[2][1], row[3][1]},
  //     {row[0][2], row[1][2], row[2][2], row[3][2]},
  //     {row[0][3], row[1][3], row[2][3], row[3][3]}
  //   }};
  // }

  // real_t Mat4::determinant() const
  // {
  //   Mat3 m11{{
  //     {row[1][1], row[1][2], row[1][3]},
  //     {row[2][1], row[2][2], row[2][3]},
  //     {row[3][1], row[3][2], row[3][3]}
  //   }};
  //   Mat3 m12{{
  //     {row[0][1], row[0][2], row[0][3]},
  //     {row[2][1], row[2][2], row[2][3]},
  //     {row[3][1], row[3][2], row[3][3]}
  //   }};
  //   Mat3 m13{{
  //     {row[0][1], row[0][2], row[0][3]},
  //     {row[1][1], row[1][2], row[1][3]},
  //     {row[3][1], row[3][2], row[3][3]}
  //   }};
  //   Mat3 m14{{
  //     {row[0][1], row[0][2], row[0][3]},
  //     {row[1][1], row[1][2], row[1][3]},
  //     {row[2][1], row[2][2], row[2][3]}
  //   }};

  //   return (
  //     row[0][0] * m11.determinant() - 
  //     row[1][0] * m12.determinant() + 
  //     row[2][0] * m13.determinant() -
  //     row[3][0] * m14.determinant()
  //   );
  // }

  // Mat4 Mat4::cofactor() const
  // {
  //   Mat4 result;
  //   for (int i = 0; i <  4; i++)
  //   {
  //     for (int j = 0; j < 4; j++)
  //     {
  //       Mat3 m_ij{{
  //         {row[(i+1) % 4][(j+1) % 4], row[(i+1) % 4][(j+2) % 4], row[(i+1) % 4][(j+3) % 4]},
  //         {row[(i+2) % 4][(j+1) % 4], row[(i+2) % 4][(j+2) % 4], row[(i+2) % 4][(j+3) % 4]},
  //         {row[(i+3) % 4][(j+1) % 4], row[(i+3) % 4][(j+2) % 4], row[(i+3) % 4][(j+3) % 4]}
  //       }};
  //       result[j][i] = (-2 * ((i + j) % 2) + 1) * m_ij.determinant();

  //       // real_t det_ij = (
  //       //   row[(i+1) % 4][(j+1) % 4] * (row[(i+2) % 4][(j+2) % 4] * row[(i+3) % 4][(j+3) % 4] - row[(i+2) % 4][(j+3) % 4] * row[(i+3) % 4][(j+2) % 4]) - 
  //       //   row[(i+2) % 4][(j+1) % 4] * (row[(i+1) % 4][(j+2) % 4] * row[(i+3) % 4][(j+3) % 4] - row[(i+1) % 4][(j+3) % 4] * row[(i+3) % 4][(j+2) % 4]) + 
  //       //   row[(i+3) % 4][(j+1) % 4] * (row[(i+1) % 4][(j+2) % 4] * row[(i+2) % 4][(j+3) % 4] - row[(i+1) % 4][(j+3) % 4] * row[(i+2) % 4][(j+2) % 4])
  //       // );
  //       // result[j][i] = (-2 * ((i + j) % 2) + 1) * det_ij;
  //     }
  //   }
  //   return result;
  // }

  // Mat4 Mat4::adjoint() const
  // {
  //   return cofactor().transpose();
  // }

  // Mat4 Mat4::inverse() const
  // {
  //   real_t det = determinant();

  //   if (approx_equal(det, 0.0f))
  //     return Mat4::zero;

  //   return (adjoint() / det);
  // }

  // bool Mat4::is_affine() const
  // {
  //   return (
  //     row[0][3] == 0 &&
  //     row[1][3] == 0 &&
  //     row[2][3] == 0 &&
  //     row[3][3] == 1
  //   );
  // }

  // Mat4 scale(const Mat4& m, Vec3 scaling)
  // {
  //   return Mat4{{
  //     m[0] * scaling[0],
  //     m[1] * scaling[1],
  //     m[2] * scaling[2],
  //     m[3]
  //   }};
  // }

  // Mat4 scale(Vec3 scaling)
  // {
  //   return scale(Mat4::identity, scaling);
  // }

  // Mat4 rotate(const Mat4& m, real_t angle, Vec3 axis)
  // {
  //   const real_t a = angle;
  //   const real_t c = cos(a);
  //   const real_t s = sin(a);

  //   Vec3 ax(normalize(axis));
  //   Vec3 axinv((1.0f - c) * ax);

  //   Mat4 rot; // TODO: make mat3
  //   real_t r00 = c + axinv[0] * ax[0];
  //   real_t r01 = axinv[0] * ax[1] + s * ax[2];
  //   real_t r02 = axinv[0] * ax[2] - s * ax[1];

  //   real_t r10 = axinv[1] * ax[0] - s * ax[2];
  //   real_t r11 = c + axinv[1] * ax[1];
  //   real_t r12 = axinv[1] * ax[2] + s * ax[0];

  //   real_t r20 = axinv[2] * ax[0] + s * ax[1];
  //   real_t r21 = axinv[2] * ax[1] - s * ax[0];
  //   real_t r22 = c + axinv[2] * ax[2];

  //   return Mat4{{
  //     m[0] * r00 + m[1] * r01 + m[2] * r02,
  //     m[0] * r10 + m[1] * r11 + m[2] * r12,
  //     m[0] * r20 + m[1] * r21 + m[2] * r22,
  //     m[3]
  //   }};
  // }

  // Mat4 rotate(real_t angle, Vec3 axis)
  // {
  //   return rotate(Mat4::identity, angle, axis);
  // }

  // Mat4 translate(const Mat4& m, Vec3 distance)
  // {
  //   return Mat4{{
  //     m[0],
  //     m[1],
  //     m[2],
  //     m[0] * distance[0] + m[1] * distance[1] + m[2] * distance[2] + m[3]
  //   }};
  // }

  // Mat4 translate(Vec3 distance)
  // {
  //   return translate(Mat4::identity, distance);
  // }

  // Mat4 ortho(real_t left, real_t right, real_t top, real_t bottom, real_t near, real_t far)
  // {
  //   real_t m00 = 2.0f / (right - left);
  //   real_t m11 = 2.0f / (top - bottom);
  //   real_t m30 = -(right + left) / (right - left);
  //   real_t m31 = -(top + bottom) / (top - bottom);
  //   real_t m32 = -(far + near) / (far - near);

  //   return Mat4{{
  //     {m00, 0,   0,   0},
  //     {0,   m11, 0,   0},
  //     {0,   0,   0,   0},
  //     {m30, m31, m32, 1}
  //   }};
  // }

  // Mat4 ortho(real_t width, real_t height, real_t near, real_t far)
  // {
  //   real_t right = 0.5f * width;
  //   real_t top = 0.5f * height;

  //   real_t m00 = 1.0f / right;
  //   real_t m11 = 1.0f / top;
  //   real_t m22 = -2.0f / far - near;
  //   real_t m32 = -(far + near) / (far - near);

  //   return Mat4{{
  //     {m00, 0,   0,   0},
  //     {0,   m11, 0,   0},
  //     {0,   0,   m22, 0},
  //     {0,   0,   m32, 1}
  //   }};
  // }

  // Mat4 perspective(real_t left, real_t right, real_t top, real_t bottom, real_t near, real_t far)
  // {
  //   real_t m00 = 2.0f * near / (right - left);
  //   real_t m11 = 2.0f * near / (top - bottom);
  //   real_t m20 = (right + left) / (right - left);
  //   real_t m21 = (top + bottom) / (top - bottom);
  //   real_t m22 = -(far + near) / (far - near);
  //   real_t m23 = -1.0f;
  //   real_t m32 = -2.0f * far * near / (far - near);

  //   return Mat4{{
  //     {m00, 0,   0,   0  },
  //     {0,   m11, 0,   0  },
  //     {m20, m21, m22, m23},
  //     {0,   0,   m32, 1  }
  //   }};
  // }

  // Mat4 perspective(real_t fov_y, real_t aspect, real_t near, real_t far)
  // {
  //   const real_t tan_fov_y2 = tan(fov_y / 2.0f);

  //   real_t m00 = 1.0f / (aspect * tan_fov_y2);
  //   real_t m11 = 1.0f / tan_fov_y2;
  //   real_t m22 = far / (near - far);
  //   real_t m23 = -1.0f;
  //   real_t m32 = -far * near / (far - near);

  //   return Mat4{{
  //     {m00, 0,   0,   0  },
  //     {0,   m11, 0,   0  },
  //     {0,   0,   m22, m23},
  //     {0,   0,   m32, 1  }
  //   }};
  // }

#pragma endregion
}
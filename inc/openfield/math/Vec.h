#ifndef VEC_H_
#define VEC_H_

#include <ostream>
#include <initializer_list>
#include <cassert>
#include <cmath>
#include <boost/lexical_cast.hpp>

namespace openfield {
namespace math {

template <int N, typename T>
class Vec
{
  public:
    Vec() {}

    Vec(const T &v) {
      for(size_t i = 0; i < N; ++i) {
        this->vec[i] = v;
      }
    }

    Vec(const Vec<N, T> &v) {
      for(size_t i = 0; i < N; ++i) {
        this->vec[i] = v[i];
      }
    }

    Vec(std::initializer_list<T> l) {
      assert(l.size() == N);
      size_t i = 0;
      for(T value : l) {
        this->vec[i] = value;
        ++i;
      }
    }

    const T operator[](size_t i) const {
      return this->vec[i];
    }

    const Vec<N, T>& operator= (const Vec<N, T> v) {
      for(size_t i = 0; i < N; ++i) {
        this->vec[i] = v[i];
      }
      return *this;
    }
    
    T& operator[](size_t i) {
      return this->vec[i];
    }

    const T* ptr() const {
      return vec;
    }
  protected:
    T vec[N];
};

template <int N, typename T>
const T dot(const Vec<N, T> &u, const Vec<N, T> &v) {
  T sum = static_cast<T>(0);
  for(size_t i = 0; i < N; ++i) {
    sum += u[i] * v[i];
  }
  return sum;
}

template <typename T>
const Vec<3, T> cross(const Vec<3, T> &u, const Vec<3, T> &v) {
  return Vec<3, T>({
   u[1] * v[2] - u[2] * v[1],
   u[2] * v[0] - u[0] * v[2],
   u[0] * v[1] - u[1] * v[0]
  });
}

//! In-place clamp
template <int N, typename T>
void clamp(Vec<N, T> &v, const Vec<N, T> &lo, const Vec<N, T> &hi) {
  for(size_t i = 0; i < N; ++i) {
    v[i] = std::max(lo[i], std::min(v[i], hi[i]));
  }
}

//! In place rotate
template <typename T>
void irotate(Vec<3, T> &v, const Vec<3, T> &axis, double theta) {
  v = v * cos(theta) +
      axis * (v * axis) * (1 - cos(theta)) +
      (v ^ axis) * sin(theta);
}

//! Out of place rotate
template <typename T>
const Vec<3, T> rotate(const Vec<3, T> &v, const Vec<3, T> &axis, double theta) {
  Vec<3, T> out(v);
  irotate(out, axis, theta);
  return out;
}

template <int N, typename T>
T norm2(const Vec<N, T> &u) {
  return std::sqrt(dot(u, u));
}

template <int N, typename T>
void normalize(Vec<N, T> &u) {
  u /= norm2(u);
}

template <int N, typename T>
const Vec<N, T> unit(const Vec<N, T> &u) {
  return u / norm2(u);
}

template <int N, typename T>
const Vec<N, T> operator+ (const Vec<N, T> &u, const Vec<N, T> &v) {
  Vec<N, T> out;
  for(size_t i = 0; i < N; ++i)
  {
    out[i] = u[i] + v[i];
  }
  return out;
}

template <int N, typename T>
void operator+= (Vec<N, T> &u, const Vec<N, T> &v) {
  for(size_t i = 0; i < N; ++i) {
    u[i] += v[i];
  }
}

template <int N, typename T>
const Vec<N, T> operator- (const Vec<N, T> &u) {
  Vec<N, T> out;
  for(size_t i = 0; i < N; ++i) {
    out[i] = -u[i];
  }
  return out;
}

template <int N, typename T>
const Vec<N, T> operator- (const Vec<N, T> &u, const Vec<N, T> &v) {
  Vec<N, T> out;
  for(size_t i = 0; i < N; ++i) {
    out[i] = u[i] - v[i];
  }
  return out;
}

template <int N, typename T>
void operator-= (Vec<N, T> &u, const Vec<N, T> &v) {
  for(size_t i = 0; i < N; ++i) {
    u[i] -= v[i];
  }
}

template <int N, typename T>
std::ostream& operator<< (std::ostream& os, const Vec<N, T> &v) {
  for(size_t i = 0; i < N; ++i) {
    os << v[i];
    if(i != N-1) {
      os << " ";
    }
  }
  return os;
}

template <int N, typename T>
std::istream& operator>> (std::istream& is, Vec<N, T> &v) {
  std::string buffer;
  for(size_t i = 0; i < N; ++i) {
    is >> buffer;
    v[i] = boost::lexical_cast<T>(buffer);
  }
  return is;
}

template <int N, typename T>
float operator* (const Vec<N, T> &u, const Vec<N, T> &v) {
  return dot(u, v);
}

template <typename T>
const Vec<3, T> operator^ (const Vec<3, T> &u, const Vec<3, T> &v) {
  return cross(u, v);
}

template <int N, typename T, typename U>
const Vec<N, T> operator* (const Vec<N, T> &u, U v) {
  Vec<N, T> out;
  const T vv = static_cast<T>(v);
  for(size_t i = 0; i < N; ++i) {
    out[i] = u[i] * vv;
  }
  return out;
}

template <int N, typename T, typename U>
const Vec<N, T> operator* (U v, const Vec<N, T> &u) {
  return u * v;
}

template <int N, typename T, typename U>
void operator*= (Vec<N, T> &u, U v) {
  const T vv = static_cast<T>(v);
  for(size_t i = 0; i < N; ++i) {
    u[i] *= vv;
  }
}

template <int N, typename T, typename U>
const Vec<N, T> operator/ (const Vec<N, T> &u, U v) {
  Vec<N, T> out;
  const T vv = static_cast<T>(v);
  for(size_t i = 0; i < N; ++i) {
    out[i] = u[i] / vv;
  }
  return out;
}

template <int N, typename T, typename U>
void operator/= (Vec<N, T> &u, U v) {
  const T vv = static_cast<T>(v);
  for(size_t i = 0; i < N; ++i) {
    u[i] /= vv;
  }
}


typedef Vec<2, bool> Vec2b;
typedef Vec<3, bool> Vec3b;
typedef Vec<4, bool> Vec4b;
typedef Vec<2, int> Vec2i;
typedef Vec<3, int> Vec3i;
typedef Vec<4, int> Vec4i;
typedef Vec<2, float> Vec2f;
typedef Vec<3, float> Vec3f;
typedef Vec<4, float> Vec4f;
typedef Vec<2, double> Vec2d;
typedef Vec<3, double> Vec3d;
typedef Vec<4, double> Vec4d;

} // namespace math
} // namespace openfield

#endif

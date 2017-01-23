#pragma once
#include <math.h>
#include <climits>
#include <vector>

#define FLOAT_MAX 1E10

namespace KS
{
  template<typename numerical_type>
  class Vec2
  {
  private:
    static numerical_type calc_mag(const numerical_type &x, const numerical_type &y) {
      return sqrt((x * x) + (y * y));
    }

  public:
    Vec2()
      : x{ 0 }, y{ 0 }, mag(0) {}
    Vec2(const Vec2 &v)
      : x{ v.x }, y{ v.y }, mag{ v.mag } {}
    Vec2(const numerical_type &_x, const numerical_type &_y) : x(_x), y(_y), mag(calc_mag(_x, _y)) {}

    void operator = (const Vec2 &other) {
      x = other.x;
      y = other.y;
      mag = other.mag;
    }

    operator bool() const {
      return ((x < FLOAT_MAX) && (y < FLOAT_MAX));
    }

    Vec2 operator+(const Vec2 &other) {
      return Vec2{ this->x + other.x, this->y + other.y };
    }

    Vec2 operator-(const Vec2 &other) {
      return Vec2{ this->x - other.x, this->y - other.y };
    }
    Vec2 operator*(const numerical_type &other) {
      return Vec2{ this->x * other, this->y * other };
    }

    Vec2 operator/(const numerical_type &other) {
      return Vec2{ this->x / other, this->y / other };
    }
    numerical_type operator*(const Vec2 &other) {
      return ((this->x * other.x) + (this->y * other.y));
    }
    void operator+=(const Vec2 &other) {
      this->x += other.x;
      this->y += other.y;
      mag = calc_mag(this->x, this->y);
    }
    void operator-=(const Vec2 &other) {
      this->x -= other.x;
      this->y -= other.y;
      mag = calc_mag(this->x, this->y);
    }
    void operator*=(const numerical_type &other) {
      this->x *= other;
      this->y *= other;
      mag = calc_mag(this->x, this->y);
    }
    void operator/=(const numerical_type &other) {
      this->x /= other;
      this->y /= other;
      mag = calc_mag(this->x, this->y);
    }

    static numerical_type Dot(const Vec2 &a, const Vec2 &b) {
      return ((a.x * b.x) + (a.y * b.y));
    }

    static float cos_theta(const Vec2 &a, const Vec2 &b) {
      numerical_type dot_product = ((a.x * b.x + a.y * b.y));
      numerical_type mags = calc_mag(a.x, a.y) * calc_mag(b.x, b.y);

      return dot_product / mags;
    }

    static void normalize(Vec2 &v) {
      numerical_type mag = calc_mag(v.x, v.y);
      v.x /= mag;
      v.y /= mag;
    }

    static float Cross2D(const Vec2<numerical_type> &v1, const Vec2<numerical_type> &v2) {
      return ((v1.x * v2.y) - (v1.y * v2.x));
    }

    static float DistanceBetween(const Vec2<numerical_type> &v1, const Vec2<numerical_type> &v2) {
      float x = v1.x - v2.x;
      float y = v1.y - v2.y;

      return (std::sqrt((x * x) + (y * y)));
    }

    float costheta = 0.f;
    numerical_type x;
    numerical_type y;
    numerical_type mag;
  };

  template<typename T>
  class PolarCoord {
  public:

    PolarCoord() : r(0), Z{ 0, 0 } {}
    PolarCoord(const T& _x, const T &_y) : Z(_x, _y) {}
    PolarCoord(const PolarCoord &p) : Z(p.Z), r(p.r) {}

    void ConvertFromVec2(const Vec2<T> &vec) {
      Z.x = vec.x;
      Z.y = vec.y;
      r = Abs();
    }

    T Re() const {
      return Z.x;
    }

    T Im() const {
      return Z.y;
    }

    T Abs() const {
      return std::sqrt((Z.x * Z.x) + (Z.y * Z.y));
    }

    Vec2<T> Z;
    T r;
  };

}

#pragma once
#include <cmath>
#include <iostream>

struct Point {
  double x = 0.0;
  double y = 0.0;

  bool operator==(const Point &other) const {
    return std::abs(x - other.x) < 1e-8 && std::abs(y - other.y) < 1e-8;
  }
  bool operator!=(const Point &other) const { return !(*this == other); }
};

class Figure {
public:
  Figure() = default;
  virtual ~Figure() = default;

  virtual Point center() const = 0;

  virtual double area() const = 0;

  virtual void print(std::ostream &os) const = 0;

  virtual void read(std::istream &is) = 0;

  virtual Figure *clone() const = 0;

  explicit operator double() const { return area(); }

  Figure(const Figure &) = default;
  Figure(Figure &&) noexcept = default;
  Figure &operator=(const Figure &) = default;
  Figure &operator=(Figure &&) noexcept = default;
};

std::ostream &operator<<(std::ostream &os, const Figure &f);
std::istream &operator>>(std::istream &is, Figure &f);

bool operator==(const Figure &a, const Figure &b);

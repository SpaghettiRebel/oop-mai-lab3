#pragma once
#include "figure.hpp"
#include <cmath>

class Triangle : public Figure {
public:
  Point c;
  double side;

  Triangle() : c{0, 0}, side(1.0) {}
  Triangle(Point center_, double side_) : c(center_), side(side_) {}

  Point center() const override;
  double area() const override;
  void print(std::ostream &os) const override;
  void read(std::istream &is) override;
  Figure *clone() const override;

  Triangle(const Triangle &) = default;
  Triangle(Triangle &&) noexcept = default;
  Triangle &operator=(const Triangle &) = default;
  Triangle &operator=(Triangle &&) noexcept = default;
};

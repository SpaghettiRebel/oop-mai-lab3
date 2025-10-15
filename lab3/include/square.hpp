#pragma once
#include "figure.hpp"

class Square : public Figure {
public:
  Point c;
  double side;

  Square() : c{0, 0}, side(1.0) {}
  Square(Point center_, double side_) : c(center_), side(side_) {}

  Point center() const override;
  double area() const override;
  void print(std::ostream &os) const override;
  void read(std::istream &is) override;
  Figure *clone() const override;

  Square(const Square &) = default;
  Square(Square &&) noexcept = default;
  Square &operator=(const Square &) = default;
  Square &operator=(Square &&) noexcept = default;
};

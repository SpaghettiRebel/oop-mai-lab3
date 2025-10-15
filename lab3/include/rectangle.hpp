#pragma once
#include "figure.hpp"

class Rectangle : public Figure {
public:
  Point c;
  double width;
  double height;

  Rectangle() : c{0, 0}, width(1.0), height(1.0) {}
  Rectangle(Point center_, double w_, double h_)
      : c(center_), width(w_), height(h_) {}

  Point center() const override;
  double area() const override;
  void print(std::ostream &os) const override;
  void read(std::istream &is) override;
  Figure *clone() const override;

  Rectangle(const Rectangle &) = default;
  Rectangle(Rectangle &&) noexcept = default;
  Rectangle &operator=(const Rectangle &) = default;
  Rectangle &operator=(Rectangle &&) noexcept = default;
};

#pragma once
#include "figure.hpp"

class Rectangle : public Figure {
public:
  Point ll;
  Point lu;
  Point rl;
  Point ru;

  Rectangle();
  Rectangle(Point ll_, Point lu_, Point rl_, Point ru_);

  Point center() const override;
  double area() const override;
  void print(std::ostream &os) const override;
  void read(std::istream &is) override;
  Figure *clone() const override;

  Rectangle(const Rectangle &) = default;
  Rectangle(Rectangle &&) noexcept = default;
  Rectangle &operator=(const Rectangle &) = default;
  Rectangle &operator=(Rectangle &&) noexcept = default;

private:
  bool isValidRectangle() const;
  double distance(const Point &a, const Point &b) const;
};

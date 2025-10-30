#pragma once
#include "figure.hpp"

class Square : public Figure {
public:
  Point ll;
  Point lu;
  Point rl;
  Point ru;

  Square();
  Square(Point ll_, Point lu_, Point rl_, Point ru_);

  Point center() const override;
  double area() const override;
  void print(std::ostream &os) const override;
  void read(std::istream &is) override;
  Figure *clone() const override;

  Square(const Square &) = default;
  Square(Square &&) noexcept = default;
  Square &operator=(const Square &) = default;
  Square &operator=(Square &&) noexcept = default;

private:
  bool isValidSquare() const;
  double distance(const Point &a, const Point &b) const;
};

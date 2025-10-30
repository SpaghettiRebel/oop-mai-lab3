#pragma once
#include "figure.hpp"
#include <cmath>

class Triangle : public Figure {
public:
  Point ll;
  Point u;
  Point rl;

  Triangle();
  Triangle(Point ll_, Point u_, Point rl_);

  Point center() const override;
  double area() const override;
  void print(std::ostream &os) const override;
  void read(std::istream &is) override;
  Figure *clone() const override;

  Triangle(const Triangle &) = default;
  Triangle(Triangle &&) noexcept = default;
  Triangle &operator=(const Triangle &) = default;
  Triangle &operator=(Triangle &&) noexcept = default;

private:
  bool isValidTriangle() const;
  double distance(const Point &a, const Point &b) const;
};

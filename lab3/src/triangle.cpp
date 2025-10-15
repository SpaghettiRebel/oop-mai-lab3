#include "triangle.hpp"
#include <cmath>
#include <iomanip>
#include <stdexcept>

Point Triangle::center() const { return c; }

double Triangle::area() const { return std::sqrt(3.0) / 4.0 * side * side; }

void Triangle::print(std::ostream &os) const {
  const double PI = M_PI;
  double R = side / std::sqrt(3.0);

  os << "Треугольник\n" << " Координаты вершин: ";

  for (int i = 0; i < 3; ++i) {
    double ang = -PI / 2 + i * (2.0 * PI / 3.0);
    double vx = c.x + R * std::cos(ang);
    double vy = c.y + R * std::sin(ang);
    os << "(" << vx << "," << vy << ") ";
  }
}

void Triangle::read(std::istream &is) {
  is >> c.x >> c.y >> side;

  if (!is || side <= 0)
    throw std::invalid_argument("Ошибка: неправильный ввод");
}

Figure *Triangle::clone() const { return new Triangle(*this); }

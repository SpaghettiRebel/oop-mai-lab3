#include "triangle.hpp"
#include <cmath>
#include <iomanip>
#include <stdexcept>

Triangle::Triangle() : ll{0, 0}, u{0, 1}, rl{1, 0} {}

Triangle::Triangle(Point ll_, Point u_, Point rl_) : ll(ll_), u(u_), rl(rl_) {
  if (!isValidTriangle())
    throw std::invalid_argument(
        "Введены неправильные координаты вершин треугольника");
}

Point Triangle::center() const {
  return Point{(ll.x + u.x + rl.x) / 3, (ll.y + u.y + rl.y) / 3};
}

double Triangle::distance(const Point &a, const Point &b) const {
  return std::hypot(a.x - b.x, a.y - b.y);
}

double Triangle::area() const {
  double a = distance(ll, u);
  double b = distance(u, rl);
  double c = distance(rl, ll);
  double s = (a + b + c) / 2;
  return std::sqrt(s * (s - a) * (s - b) * (s - c));
}

void Triangle::print(std::ostream &os) const {
  os << "Треугольник("
     << "(" << ll.x << "," << ll.y << "), "
     << "(" << u.x << "," << u.y << "), "
     << "(" << rl.x << "," << rl.y << ")) ";
  os << "Площадь: " << area();
}

void Triangle::read(std::istream &is) {
  double x, y;

  is >> x >> y;
  ll = Point{x, y};

  is >> x >> y;
  u = Point{x, y};

  is >> x >> y;
  rl = Point{x, y};

  if (!isValidTriangle())
    throw std::invalid_argument(
        "Введены неправильные координаты вершин треугольника");
}

bool Triangle::isValidTriangle() const {
  double a = distance(ll, u);
  double b = distance(u, rl);
  double c = distance(rl, ll);

  // Проверка треугольного неравенства
  return a > 0 && b > 0 && c > 0 && a + b > c && b + c > a && c + a > b;
}

Figure *Triangle::clone() const { return new Triangle(*this); }

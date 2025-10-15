#include "rectangle.hpp"
#include <stdexcept>

Point Rectangle::center() const { return c; }

double Rectangle::area() const { return width * height; }

void Rectangle::print(std::ostream &os) const {
  double hx = width / 2.0;
  double hy = height / 2.0;

  os << "Прямоугольник\n" << " Координаты вершин: ";

  os << "(" << c.x - hx << "," << c.y - hy << ") ";
  os << "(" << c.x + hx << "," << c.y - hy << ") ";
  os << "(" << c.x + hx << "," << c.y + hy << ") ";
  os << "(" << c.x - hx << "," << c.y + hy << ") ";
}

void Rectangle::read(std::istream &is) {
  is >> c.x >> c.y >> width >> height;

  if (!is || width <= 0 || height <= 0)
    throw std::invalid_argument("Ошибка: неправильный ввод");
}

Figure *Rectangle::clone() const { return new Rectangle(*this); }

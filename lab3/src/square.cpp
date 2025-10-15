#include "square.hpp"
#include <cmath>
#include <sstream>
#include <stdexcept>

Point Square::center() const { return c; }

double Square::area() const { return side * side; }

void Square::print(std::ostream &os) const {
  double h = side / 2.0;

  os << "Квадрат\n" << " Координаты вершин: ";

  os << "(" << c.x - h << "," << c.y - h << ") ";
  os << "(" << c.x + h << "," << c.y - h << ") ";
  os << "(" << c.x + h << "," << c.y + h << ") ";
  os << "(" << c.x - h << "," << c.y + h << ")";
}

void Square::read(std::istream &is) {
  is >> c.x >> c.y >> side;

  if (!is || side <= 0) {
    throw std::invalid_argument("Ошибка: неправильный ввод");
  }
}

Figure *Square::clone() const { return new Square(*this); }

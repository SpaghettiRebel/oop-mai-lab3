#include "square.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <vector>

Square::Square() : ll{0, 0}, lu{0, 1}, rl{1, 0}, ru{1, 1} {}

Square::Square(Point ll_, Point lu_, Point rl_, Point ru_)
    : ll(ll_), lu(lu_), rl(rl_), ru(ru_) {
  if (!isValidSquare())
    throw std::invalid_argument("Введены неправильные координаты квадрата");
}

Point Square::center() const {
  return Point{(ll.x + lu.x + rl.x + ru.x) / 4.0,
               (ll.y + lu.y + rl.y + ru.y) / 4.0};
}

double Square::area() const { return distance(ll, rl) * distance(ll, lu); }

void Square::print(std::ostream &os) const {
  os << "Квадрат(" << "(" << ll.x << "," << ll.y << "), "
     << "(" << lu.x << "," << lu.y << "), "
     << "(" << rl.x << "," << rl.y << "), "
     << "(" << ru.x << "," << ru.y << ")) ";
  os << " Площадь: " << area();
}

void Square::read(std::istream &is) {
  std::vector<Point> pts(4);
  for (int i = 0; i < 4; ++i)
    is >> pts[i].x >> pts[i].y;

  auto ll_it = std::min_element(
      pts.begin(), pts.end(),
      [](const Point &a, const Point &b) { return (a.x + a.y) < (b.x + b.y); });
  ll = *ll_it;
  auto ru_it = std::max_element(
      pts.begin(), pts.end(),
      [](const Point &a, const Point &b) { return (a.x + a.y) < (b.x + b.y); });
  ru = *ru_it;

  std::vector<Point> remains;
  for (const auto &pt : pts)
    if (pt != ll && pt != ru)
      remains.push_back(pt);

  if (remains[0].y > remains[1].y) {
    lu = remains[0];
    rl = remains[1];
  } else {
    lu = remains[1];
    rl = remains[0];
  }

  if (!isValidSquare())
    throw std::invalid_argument("Введены неправильные координаты квадрата");
}

double Square::distance(const Point &a, const Point &b) const {
  return std::hypot(a.x - b.x, a.y - b.y);
}

bool Square::isValidSquare() const {
  double lenAB = distance(ll, lu);
  double lenBC = distance(lu, ru);
  double lenCD = distance(ru, rl);
  double lenDA = distance(rl, ll);

  const double eps = 1e-8;
  bool sidesEqual = std::abs(lenAB - lenBC) < eps &&
                    std::abs(lenBC - lenCD) < eps &&
                    std::abs(lenCD - lenDA) < eps && lenAB > eps;

  Point AB{lu.x - ll.x, lu.y - ll.y};
  Point BC{ru.x - lu.x, ru.y - lu.y};
  Point CD{rl.x - ru.x, rl.y - ru.y};
  Point DA{ll.x - rl.x, ll.y - rl.y};

  auto dot = [](const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
  };

  bool rightAngles = std::abs(dot(AB, BC)) < eps &&
                     std::abs(dot(BC, CD)) < eps &&
                     std::abs(dot(CD, DA)) < eps && std::abs(dot(DA, AB)) < eps;

  return sidesEqual && rightAngles;
}

Figure *Square::clone() const { return new Square(*this); }

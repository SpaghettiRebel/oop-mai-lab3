#include "rectangle.hpp"
#include <stdexcept>
#include <vector>

Rectangle::Rectangle() : ll{0, 0}, lu{0, 1}, rl{1, 0}, ru{1, 1} {}

Rectangle::Rectangle(Point ll_, Point lu_, Point rl_, Point ru_)
    : ll(ll_), lu(lu_), rl(rl_), ru(ru_) {
  if (!isValidRectangle())
    throw std::invalid_argument("Введены неправильные координаты");
}

Point Rectangle::center() const {
  return Point{(ll.x + lu.x + rl.x + ru.x) / 4,
               (ll.y + lu.y + rl.y + ru.y) / 4};
}

double Rectangle::area() const { return distance(ll, rl) * distance(ll, lu); }

void Rectangle::print(std::ostream &os) const {
  os << "Прямоугольник(" << "(" << ll.x << "," << ll.y << ")" << ", " << "("
     << lu.x << "," << lu.y << ")" << ", " << "(" << rl.x << "," << rl.y << ")"
     << ", " << "(" << ru.x << "," << ru.y << ")" << ")";
  os << " Площадь: " << area();
}

void Rectangle::read(std::istream &is) {
  std::vector<Point> pts(4);
  for (int i = 0; i < 4; ++i)
    is >> pts[i].x >> pts[i].y;

  double min_x = pts[0].x, max_x = pts[0].x;
  double min_y = pts[0].y, max_y = pts[0].y;
  for (const auto &pt : pts) {
    if (pt.x < min_x)
      min_x = pt.x;
    if (pt.x > max_x)
      max_x = pt.x;
    if (pt.y < min_y)
      min_y = pt.y;
    if (pt.y > max_y)
      max_y = pt.y;
  }

  // Присваиваем вершины:
  for (const auto &pt : pts) {
    if (std::abs(pt.x - min_x) < 1e-8 && std::abs(pt.y - min_y) < 1e-8)
      ll = pt;
    else if (std::abs(pt.x - min_x) < 1e-8 && std::abs(pt.y - max_y) < 1e-8)
      lu = pt;
    else if (std::abs(pt.x - max_x) < 1e-8 && std::abs(pt.y - min_y) < 1e-8)
      rl = pt;
    else if (std::abs(pt.x - max_x) < 1e-8 && std::abs(pt.y - max_y) < 1e-8)
      ru = pt;
  }

  if (!isValidRectangle())
    throw std::invalid_argument("Введены неправильные координаты");
}

double Rectangle::distance(const Point &a, const Point &b) const {
  return std::hypot(a.x - b.x, a.y - b.y);
}

bool Rectangle::isValidRectangle() const {
  Point AB{lu.x - ll.x, lu.y - ll.y};
  Point BC{ru.x - lu.x, ru.y - lu.y};
  Point CD{rl.x - ru.x, rl.y - ru.y};
  Point DA{ll.x - rl.x, ll.y - rl.y};

  auto dot = [](const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
  };

  bool angleA = dot(AB, DA) == 0;
  bool angleB = dot(BC, AB) == 0;
  bool angleC = dot(CD, BC) == 0;
  bool angleD = dot(DA, CD) == 0;

  double lenAB = distance(ll, lu);
  double lenBC = distance(lu, ru);
  double lenCD = distance(ru, rl);
  double lenDA = distance(rl, ll);

  bool sidesAB_CD = std::abs(lenAB - lenCD) < 1e-8;
  bool sidesBC_DA = std::abs(lenBC - lenDA) < 1e-8;

  return angleA && angleB && angleC && angleD && sidesAB_CD && sidesBC_DA;
}

Figure *Rectangle::clone() const { return new Rectangle(*this); }

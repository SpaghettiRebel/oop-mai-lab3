#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

struct Point {
  double x = 0.0;
  double y = 0.0;
};

inline bool close(double a, double b, double eps = 1e-6) {
  return std::fabs(a - b) < eps;
}
inline bool close(const Point &a, const Point &b, double eps = 1e-6) {
  return close(a.x, b.x, eps) && close(a.y, b.y, eps);
}

// --------- Figure (base) ----------
class Figure {
public:
  virtual ~Figure() = default;

  // Центр фигуры (геометрический центр)
  virtual Point center() const = 0;

  // Площадь
  virtual double area() const = 0;

  // Печать (в формате: имя и данные; производный реализует координаты вершин)
  virtual void print(std::ostream &os) const = 0;

  // Чтение данных фигуры (ввод параметров)
  virtual void read(std::istream &is) = 0;

  // Полиморфное клонирование (для копирования фигур через указатель)
  virtual std::unique_ptr<Figure> clone() const = 0;

  // Приведение к double -> площадь
  explicit operator double() const { return area(); }

  // Тип-строка (для удобства при печати)
  virtual std::string type_name() const = 0;
};

// Операторы ввода/вывода (неглобальные тела, используют виртуальные методы)
inline std::ostream &operator<<(std::ostream &os, const Figure &f) {
  f.print(os);
  return os;
}
inline std::istream &operator>>(std::istream &is, Figure &f) {
  f.read(is);
  return is;
}

// Сравнение: по площади и центру
inline bool operator==(const Figure &a, const Figure &b) {
  return close(a.area(), b.area()) && close(a.center(), b.center());
}

// --------- EquilateralTriangle ----------
class EquilateralTriangle : public Figure {
public:
  // храним центр и сторону
  Point c;
  double side = 1.0;

  EquilateralTriangle() = default;
  EquilateralTriangle(Point center_, double side_) : c(center_), side(side_) {}

  Point center() const override { return c; }

  double area() const override { return (std::sqrt(3.0) / 4.0) * side * side; }

  void print(std::ostream &os) const override {
    // Вычислим координаты вершин, предполагая, что центр = centroid
    // Для равностороннего треугольника расстояние от центра до вершины:
    // Rv = side / sqrt(3)
    double R = side / std::sqrt(3.0);
    // первая вершина на угле -90° (чтобы треугольник "стоял"), остальные на
    // +120°
    const double PI = std::acos(-1.0);
    std::vector<Point> v(3);
    for (int i = 0; i < 3; ++i) {
      double ang = -PI / 2 + i * (2.0 * PI / 3.0);
      v[i].x = c.x + R * std::cos(ang);
      v[i].y = c.y + R * std::sin(ang);
    }

    os << "EquilateralTriangle center=(" << c.x << "," << c.y
       << ") side=" << side << " vertices: ";
    for (auto &p : v)
      os << "(" << p.x << "," << p.y << ") ";
    os << " area=" << area();
  }

  void read(std::istream &is) override {
    // ожидаем: c.x c.y side
    is >> c.x >> c.y >> side;
    if (!is || side <= 0)
      throw std::runtime_error("Invalid triangle input");
  }

  std::unique_ptr<Figure> clone() const override {
    return std::make_unique<EquilateralTriangle>(*this);
  }

  std::string type_name() const override { return "Triangle"; }
};

// --------- Square ----------
class Square : public Figure {
public:
  Point c;
  double side = 1.0;

  Square() = default;
  Square(Point center_, double side_) : c(center_), side(side_) {}

  Point center() const override { return c; }

  double area() const override { return side * side; }

  void print(std::ostream &os) const override {
    // квадрат, стороны параллельны осям (для простоты)
    double half = side / 2.0;
    std::vector<Point> v = {{c.x - half, c.y - half},
                            {c.x + half, c.y - half},
                            {c.x + half, c.y + half},
                            {c.x - half, c.y + half}};
    os << "Square center=(" << c.x << "," << c.y << ") side=" << side
       << " vertices: ";
    for (auto &p : v)
      os << "(" << p.x << "," << p.y << ") ";
    os << " area=" << area();
  }

  void read(std::istream &is) override {
    // ввод: c.x c.y side
    is >> c.x >> c.y >> side;
    if (!is || side <= 0)
      throw std::runtime_error("Invalid square input");
  }

  std::unique_ptr<Figure> clone() const override {
    return std::make_unique<Square>(*this);
  }

  std::string type_name() const override { return "Square"; }
};

// --------- Rectangle ----------
class Rectangle : public Figure {
public:
  Point c;
  double width = 1.0;
  double height = 1.0;

  Rectangle() = default;
  Rectangle(Point center_, double w_, double h_)
      : c(center_), width(w_), height(h_) {}

  Point center() const override { return c; }

  double area() const override { return width * height; }

  void print(std::ostream &os) const override {
    double hx = width / 2.0;
    double hy = height / 2.0;
    std::vector<Point> v = {{c.x - hx, c.y - hy},
                            {c.x + hx, c.y - hy},
                            {c.x + hx, c.y + hy},
                            {c.x - hx, c.y + hy}};
    os << "Rectangle center=(" << c.x << "," << c.y << ") w=" << width
       << " h=" << height << " vertices: ";
    for (auto &p : v)
      os << "(" << p.x << "," << p.y << ") ";
    os << " area=" << area();
  }

  void read(std::istream &is) override {
    // ввод: c.x c.y width height
    is >> c.x >> c.y >> width >> height;
    if (!is || width <= 0 || height <= 0)
      throw std::runtime_error("Invalid rectangle input");
  }

  std::unique_ptr<Figure> clone() const override {
    return std::make_unique<Rectangle>(*this);
  }

  std::string type_name() const override { return "Rectangle"; }
};

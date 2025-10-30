#include "figure.hpp"
#include "rectangle.hpp"
#include "square.hpp"
#include "triangle.hpp"

#include <cmath>
#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include <vector>

static constexpr double EPS = 1e-6;

// Функция для поиска площади в выводе
static bool output_contains_area(const std::string &out, double area) {
  std::ostringstream tmp;
  tmp << area;
  return out.find(tmp.str()) != std::string::npos;
}

// ---- SQUARE

TEST(SquareTest, AreaAndCenter) {
  // Квадрат со стороной 4, центр (1.5, -2.0)
  double h = 2.0;
  Point ll{1.5 - h, -2.0 - h};
  Point lu{1.5 - h, -2.0 + h};
  Point rl{1.5 + h, -2.0 - h};
  Point ru{1.5 + h, -2.0 + h};
  Square s(ll, lu, rl, ru);
  EXPECT_NEAR(s.area(), 16.0, EPS);
  Point c = s.center();
  EXPECT_NEAR(c.x, 1.5, EPS);
  EXPECT_NEAR(c.y, -2.0, EPS);
}

TEST(SquareTest, IOAndClone) {
  // Ввод с четырьмя вершинами
  std::istringstream in("0.0 1.0  0.0 4.5   3.5 1.0   3.5 4.5"); // ll lu rl ru
  Square s;
  EXPECT_NO_THROW(in >> s);
  EXPECT_NEAR(s.ll.x, 0.0, EPS);
  EXPECT_NEAR(s.ll.y, 1.0, EPS);
  EXPECT_NEAR(s.lu.x, 0.0, EPS);
  EXPECT_NEAR(s.lu.y, 4.5, EPS);
  EXPECT_NEAR(s.rl.x, 3.5, EPS);
  EXPECT_NEAR(s.rl.y, 1.0, EPS);
  EXPECT_NEAR(s.ru.x, 3.5, EPS);
  EXPECT_NEAR(s.ru.y, 4.5, EPS);

  std::ostringstream out;
  out << s;
  std::string o = out.str();
  EXPECT_FALSE(o.empty());
  EXPECT_TRUE(output_contains_area(o, s.area()));

  // clone
  Figure *copy = s.clone();
  Square *scopy = dynamic_cast<Square *>(copy);
  ASSERT_NE(scopy, nullptr);
  EXPECT_NEAR(scopy->ll.x, s.ll.x, EPS);
  EXPECT_NEAR(scopy->lu.y, s.lu.y, EPS);
  delete copy;
}

// ---- TRIANGLE

TEST(TriangleTest, AreaAndVertices) {
  // Правильный треугольник со стороной 2
  double h = std::sqrt(3.0) / 2.0 * 2.0;
  Point a{0.0, 0.0};
  Point b{2.0, 0.0};
  Point c{1.0, h};
  Triangle t(a, b, c);
  EXPECT_NEAR(t.area(), std::sqrt(3.0), EPS);
  Point center = t.center();
  EXPECT_NEAR(center.x, 1.0, EPS);
  EXPECT_NEAR(center.y, h / 3.0, EPS);

  std::ostringstream out;
  out << t;
  std::string o = out.str();
  EXPECT_FALSE(o.empty());
  EXPECT_TRUE(output_contains_area(o, t.area()));
}

// ---- RECTANGLE

TEST(RectangleTest, AreaReadAndPrint) {
  Rectangle r;
  // Прямоугольник 5x8, левый нижний (2,3)
  std::istringstream in("2.0 3.0  2.0 11.0   7.0 3.0   7.0 11.0");
  EXPECT_NO_THROW(in >> r);
  EXPECT_NEAR(r.area(), 40.0, EPS);
  std::ostringstream out;
  out << r;
  std::string o = out.str();
  EXPECT_FALSE(o.empty());
  EXPECT_TRUE(output_contains_area(o, r.area()));
}

// ---- INVALID INPUT

TEST(InvalidInput, NegativeDimensionsThrows) {
  Square s;
  // невалидные координаты (нарушено равенство сторон)
  std::istringstream in1("0 0  0 1  2 0  2 2"); // не квадрат
  EXPECT_ANY_THROW(in1 >> s);

  Rectangle r;
  std::istringstream in2("0 0  0 0  0 0  0 0"); // нулевые стороны
  EXPECT_ANY_THROW(in2 >> r);

  Triangle t;
  std::istringstream in3("0 0  0 0  0 0"); // одна точка
  EXPECT_ANY_THROW(in3 >> t);
}

// ---- POLYMORPHIC (сравнение + площадь)

TEST(PolymorphicEqualityAndSumArea, EqualAndSum) {
  Square s1(Point{0, 0}, Point{0, 2}, Point{2, 0}, Point{2, 2});
  Square s2(Point{0, 0}, Point{0, 2}, Point{2, 0}, Point{2, 2});
  EXPECT_TRUE(operator==(s1, s2));

  std::vector<Figure *> arr;
  arr.push_back(new Square(Point{0, 0}, Point{0, 2}, Point{2, 0}, Point{2, 2}));
  arr.push_back(
      new Rectangle(Point{0, 0}, Point{0, 3}, Point{4, 0}, Point{4, 3}));
  arr.push_back(new Triangle(Point{0, 0}, Point{2, 0},
                             Point{1, std::sqrt(3)})); // правильный треугольник

  double sum = 0.0;
  for (auto f : arr)
    sum += f->area();

  EXPECT_NEAR(sum, 4.0 + 12.0 + std::sqrt(3.0), 1e-5);

  for (auto p : arr)
    delete p;
}

// ---- Копирование через базовый указатель

TEST(CloneThroughBasePointer, PolymorphicCopy) {
  Square s(Point{5, 3}, Point{5, 6}, Point{8, 3}, Point{8, 6});
  Figure *base = &s;
  Figure *copy = base->clone();
  ASSERT_NE(copy, nullptr);
  Square *sc = dynamic_cast<Square *>(copy);
  ASSERT_NE(sc, nullptr);
  EXPECT_NEAR(sc->ll.x, s.ll.x, EPS);
  delete copy;
}

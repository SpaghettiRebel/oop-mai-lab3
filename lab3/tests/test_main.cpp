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

static bool output_contains_area(const std::string &out, double area) {
  std::ostringstream tmp;
  return out.find(tmp.str()) != std::string::npos;
}

TEST(SquareTest, AreaAndCenter) {
  Point p{1.5, -2.0};
  Square s(p, 4.0);
  EXPECT_NEAR(s.area(), 16.0, EPS);
  Point c = s.center();
  EXPECT_NEAR(c.x, 1.5, EPS);
  EXPECT_NEAR(c.y, -2.0, EPS);
}

TEST(SquareTest, IOAndClone) {
  std::istringstream in("0.0 1.0 3.5");
  Square s;
  EXPECT_NO_THROW(in >> s);
  EXPECT_NEAR(s.c.x, 0.0, EPS);
  EXPECT_NEAR(s.c.y, 1.0, EPS);
  EXPECT_NEAR(s.side, 3.5, EPS);

  std::ostringstream out;
  out << s;
  std::string o = out.str();
  EXPECT_FALSE(o.empty());
  EXPECT_TRUE(output_contains_area(o, s.area()));

  // clone
  Figure *copy = s.clone();
  Square *scopy = dynamic_cast<Square *>(copy);
  ASSERT_NE(scopy, nullptr);
  EXPECT_NEAR(scopy->c.x, s.c.x, EPS);
  EXPECT_NEAR(scopy->c.y, s.c.y, EPS);
  EXPECT_NEAR(scopy->side, s.side, EPS);
  delete copy;
}

TEST(TriangleTest, AreaAndVertices) {
  Point p{0.0, 0.0};
  Triangle t(p, 2.0);
  EXPECT_NEAR(t.area(), std::sqrt(3.0), EPS);
  Point c = t.center();
  EXPECT_NEAR(c.x, 0.0, EPS);
  EXPECT_NEAR(c.y, 0.0, EPS);

  std::ostringstream out;
  out << t;
  std::string o = out.str();
  EXPECT_FALSE(o.empty());
  EXPECT_TRUE(output_contains_area(o, t.area()));
}

TEST(RectangleTest, AreaReadAndPrint) {
  Rectangle r;
  std::istringstream in("2.0 3.0 4.0 5.0");
  EXPECT_NO_THROW(in >> r);
  EXPECT_NEAR(r.area(), 20.0, EPS);
  std::ostringstream out;
  out << r;
  std::string o = out.str();
  EXPECT_FALSE(o.empty());
  EXPECT_TRUE(output_contains_area(o, r.area()));
}

TEST(InvalidInput, NegativeDimensionsThrows) {
  Square s;
  std::istringstream in1("0 0 -3");
  EXPECT_ANY_THROW(in1 >> s);

  Rectangle r;
  std::istringstream in2("0 0 -1 2");
  EXPECT_ANY_THROW(in2 >> r);

  Triangle t;
  std::istringstream in3("0 0 0");
  EXPECT_ANY_THROW(in3 >> t);
}

TEST(PolymorphicEqualityAndSumArea, EqualAndSum) {
  Square s1(Point{0, 0}, 2.0);
  Square s2(Point{0, 0}, 2.0);
  EXPECT_TRUE(operator==(s1, s2));

  std::vector<Figure *> arr;
  arr.push_back(new Square(Point{0, 0}, 2.0));
  arr.push_back(new Rectangle(Point{0, 0}, 3.0, 2.0));
  arr.push_back(new Triangle(Point{0, 0}, 2.0));

  double sum = 0.0;
  for (auto f : arr)
    sum += f->area();

  EXPECT_NEAR(sum, 4.0 + 6.0 + std::sqrt(3.0), 1e-5);

  for (auto p : arr)
    delete p;
}

TEST(CloneThroughBasePointer, PolymorphicCopy) {
  Square s(Point{5, 5}, 1.5);
  Figure *base = &s;
  Figure *copy = base->clone();
  ASSERT_NE(copy, nullptr);
  Square *sc = dynamic_cast<Square *>(copy);
  ASSERT_NE(sc, nullptr);
  EXPECT_NEAR(sc->side, s.side, EPS);
  delete copy;
}

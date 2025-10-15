#include "figure.hpp"
#include <cmath>
#include <iomanip>

static bool close(const double a, const double b, const double eps = 1e-6) {
  return std::fabs(a - b) < eps;
}
static bool close(const Point &A, const Point &B, double eps = 1e-6) {
  return close(A.x, B.x, eps) && close(A.y, B.y, eps);
}

std::ostream &operator<<(std::ostream &os, const Figure &f) {
  f.print(os);
  return os;
}

std::istream &operator>>(std::istream &is, Figure &f) {
  f.read(is);
  return is;
}

bool operator==(const Figure &a, const Figure &b) {
  return close(a.area(), b.area()) && close(a.center(), b.center());
}

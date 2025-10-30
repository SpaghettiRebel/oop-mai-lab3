#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

#include "array.hpp"
#include "rectangle.hpp"
#include "square.hpp"
#include "triangle.hpp"

int main() {
  Array arr;

  std::cout << "Введите номер действия:\n"
            << "  1: добавить треугольник\n"
            << "  2: добавить квадрат\n"
            << "  3: добавить прямоугольник\n"
            << "  p: печать всех фигур\n"
            << "  s: суммарная площадь\n"
            << "  d: удалить фигуру\n"
            << "  0: выход\n";

  while (true) {
    std::cout << "Ввод: ";
    std::string cmd;
    if (!(std::cin >> cmd))
      break;

    try {
      if (cmd == "1") {
        std::cout << "Введите координаты треугольника: ";
        Triangle *t = new Triangle();
        std::cin >> *t;
        if (!std::cin) {
          delete t;
          throw std::invalid_argument("Ошибка ввода треугольника");
        }
        arr.push_back(t);

      } else if (cmd == "2") {
        std::cout << "Введите координаты квадрата: ";
        Square *s = new Square();
        std::cin >> *s;
        if (!std::cin) {
          delete s;
          throw std::invalid_argument("Ошибка ввода квадрата");
        }
        arr.push_back(s);

      } else if (cmd == "3") {
        std::cout << "Введите координаты прямоугольника: ";
        Rectangle *r = new Rectangle();
        std::cin >> *r;
        if (!std::cin) {
          delete r;
          throw std::invalid_argument("Ошибка ввода прямоугольника");
        }
        arr.push_back(r);

      } else if (cmd == "p") {
        arr.print(std::cout);

      } else if (cmd == "s") {
        double sum = 0.0;
        for (std::size_t i = 0; i < arr.size(); ++i) {
          Figure *f = arr[i];
          if (f)
            sum += f->area();
        }
        std::cout << "  Суммарная площадь = " << sum << "\n";

      } else if (cmd == "d") {
        std::cout << "Введите индекс удаляемой фигуры (начиная с 0): ";
        std::size_t idx;
        std::cin >> idx;

        if (!std::cin) {
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cout << "  Ошибка: неправильный ввод индекса\n";
        } else if (idx >= arr.size()) {
          std::cout << "  Ошибка: неправильный индекс\n";
        } else {
          arr.erase(idx);
        }

      } else if (cmd == "0") {
        break;

      } else {
        std::cout << "Ошибка: такого варианта нет\n";
      }
    } catch (const std::exception &e) {
      std::cout << "Ошибка: " << e.what() << "\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  return 0;
}

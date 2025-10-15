#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "rectangle.hpp"
#include "square.hpp"
#include "triangle.hpp"

int main() {
  std::vector<Figure *> arr;

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
        std::cout << "Введите координаты центра треугольника и длину стороны: ";
        Triangle *t = new Triangle();
        std::cin >> *t;
        arr.push_back(t);

      } else if (cmd == "2") {
        std::cout << "Введите координаты центра квадрата и длину стороны: ";
        Square *s = new Square();
        std::cin >> *s;
        arr.push_back(s);

      } else if (cmd == "3") {
        std::cout
            << "Введите координаты центра прямоугольника и длины стороны: ";
        Rectangle *r = new Rectangle();
        std::cin >> *r;
        arr.push_back(r);

      } else if (cmd == "p") {
        for (size_t i = 0; i < arr.size(); ++i)
          std::cout << i << ": " << *arr[i] << "\n";

      } else if (cmd == "s") {
        double sum = 0.0;

        for (auto f : arr)
          sum += f->area();

        std::cout << "  Суммарная площадь = " << sum << "\n";

      } else if (cmd == "d") {
        std::cout << "Введите индекс удаляемой фигуры (начиная с 0): ";
        size_t idx;
        std::cin >> idx;

        if (idx >= arr.size())
          std::cout << "  Ошибка: неправильный индекс\n";
        else {
          delete arr[idx];
          arr.erase(arr.begin() + idx);
        }

      } else if (cmd == "0") {
        break;

      } else {
        std::cout << "Ошибка: такого варианта нет\n";
      }
    } catch (const std::exception &e) {
      std::cout << "Ошибка: " << e.what() << "\n";
      std::cin.clear();
      std::string skip;
      std::getline(std::cin, skip);
    }
  }

  for (auto p : arr)
    delete p;
  return 0;
}

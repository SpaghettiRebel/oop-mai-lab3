#pragma once

#include "figure.hpp"
#include <cstddef>
#include <initializer_list>
#include <iostream>

class Array {
public:
  Array() noexcept;
  explicit Array(std::size_t reserve_size);
  Array(const std::initializer_list<Figure *> &init);
  Array(const Array &other);
  Array(Array &&other) noexcept;
  virtual ~Array() noexcept;

  Array &operator=(const Array &other);
  Array &operator=(Array &&other) noexcept;

  void push_back(Figure *f);
  void erase(std::size_t idx);
  Figure *operator[](std::size_t idx);
  const Figure *operator[](std::size_t idx) const;
  std::size_t size() const noexcept;
  void clear() noexcept;
  void swap(Array &other) noexcept;

  Array add(const Array &other) const;
  Array remove(const Array &other) const;
  bool equals(const Array &other) const;
  std::ostream &print(std::ostream &os) const;

private:
  Figure **data_;
  std::size_t size_;
  std::size_t capacity_;

  void grow();
};

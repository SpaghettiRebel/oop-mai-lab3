#include "array.hpp"
#include <stdexcept>
#include <utility>

void Array::grow() {
  std::size_t newcap = capacity_ ? capacity_ * 2 : 1;
  Figure **newdata = new Figure *[newcap];
  for (std::size_t i = 0; i < size_; ++i)
    newdata[i] = data_[i];
  delete[] data_;
  data_ = newdata;
  capacity_ = newcap;
}

Array::Array() noexcept : data_(nullptr), size_(0), capacity_(0) {}

Array::Array(std::size_t reserve_size)
    : data_(nullptr), size_(0), capacity_(0) {
  if (reserve_size) {
    data_ = new Figure *[reserve_size];
    capacity_ = reserve_size;
  }
}

Array::Array(const std::initializer_list<Figure *> &init)
    : data_(nullptr), size_(0), capacity_(0) {
  if (init.size()) {
    data_ = new Figure *[init.size()];
    capacity_ = init.size();
    for (Figure *f : init) {
      data_[size_++] = (f ? f->clone() : nullptr);
    }
  }
}

Array::Array(const Array &other)
    : data_(nullptr), size_(other.size_), capacity_(other.size_) {
  if (capacity_) {
    data_ = new Figure *[capacity_];
    for (std::size_t i = 0; i < size_; ++i)
      data_[i] = other.data_[i] ? other.data_[i]->clone() : nullptr;
  }
}

Array::Array(Array &&other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
  other.data_ = nullptr;
  other.size_ = other.capacity_ = 0;
}

Array::~Array() noexcept {
  clear();
  delete[] data_;
}

Array &Array::operator=(const Array &other) {
  if (this == &other)
    return *this;
  Array tmp(other);
  swap(tmp);
  return *this;
}

Array &Array::operator=(Array &&other) noexcept {
  if (this == &other)
    return *this;
  clear();
  delete[] data_;
  data_ = other.data_;
  size_ = other.size_;
  capacity_ = other.capacity_;
  other.data_ = nullptr;
  other.size_ = other.capacity_ = 0;
  return *this;
}

void Array::push_back(Figure *f) {
  if (size_ == capacity_)
    grow();
  data_[size_++] = f;
}

void Array::erase(std::size_t idx) {
  if (idx >= size_)
    throw std::out_of_range("Array::erase: index out of range");
  delete data_[idx];
  for (std::size_t i = idx + 1; i < size_; ++i)
    data_[i - 1] = data_[i];
  --size_;
}

Figure *Array::operator[](std::size_t idx) {
  if (idx >= size_)
    throw std::out_of_range("Array::operator[]: index out of range");
  return data_[idx];
}

const Figure *Array::operator[](std::size_t idx) const {
  if (idx >= size_)
    throw std::out_of_range("Array::operator[]: index out of range");
  return data_[idx];
}

std::size_t Array::size() const noexcept { return size_; }

void Array::clear() noexcept {
  if (data_) {
    for (std::size_t i = 0; i < size_; ++i)
      delete data_[i];
  }
  size_ = 0;
}

void Array::swap(Array &other) noexcept {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

Array Array::add(const Array &other) const {
  Array res;
  for (std::size_t i = 0; i < size_; ++i)
    res.push_back(data_[i] ? data_[i]->clone() : nullptr);
  for (std::size_t j = 0; j < other.size_; ++j)
    res.push_back(other.data_[j] ? other.data_[j]->clone() : nullptr);
  return res;
}

Array Array::remove(const Array &other) const {
  Array res;
  for (std::size_t i = 0; i < size_; ++i) {
    Figure *f = data_[i];
    bool should_remove = false;
    for (std::size_t j = 0; j < other.size_; ++j) {
      if (f && other.data_[j] && (*f == *other.data_[j])) {
        should_remove = true;
        break;
      }
    }
    if (!should_remove)
      res.push_back(f ? f->clone() : nullptr);
  }
  return res;
}

bool Array::equals(const Array &other) const {
  if (size_ != other.size_)
    return false;
  for (std::size_t i = 0; i < size_; ++i) {
    Figure *a = data_[i];
    Figure *b = other.data_[i];
    if (a == nullptr && b == nullptr)
      continue;
    if (a == nullptr || b == nullptr)
      return false;
    if (!(*a == *b))
      return false;
  }
  return true;
}

std::ostream &Array::print(std::ostream &os) const {
  for (std::size_t i = 0; i < size_; ++i) {
    os << i << ": ";
    if (data_[i])
      os << *data_[i];
    else
      os << "(null)";
    os << '\n';
  }
  return os;
}

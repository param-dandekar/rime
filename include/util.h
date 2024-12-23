#pragma once

#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>

template <typename T> class reg {
  static_assert(std::is_integral<T>::value && std::is_unsigned<T>::value,
                "reg class requires an unsigned integral type");

private:
  T _value;

public:
  reg() : _value(0) {}
  reg(T value) : _value(value) {}

  // Implicit conversion operator
  operator T() const { return _value; }

  template <typename U> reg(const reg<U> &other) {
    static_assert(std::is_unsigned<U>::value,
                  "Conversion requires an unsigned integral type");
    _value = static_cast<T>(other.operator U());
  }

  // Assignment from reg
  reg &operator=(const reg &other) {
    _value = other._value;
    return *this;
  }

  /* // Assignment from uint8_t */
  /* reg &operator=(const uint8_t &value) { */
  /*   _value = static_cast<T>(value); */
  /*   return *this; */
  /* } */

  /* // Assignment from uint16_t */
  /* reg &operator=(const uint16_t &value) { */
  /*   _value = static_cast<T>(value); */
  /*   return *this; */
  /* } */

  // Pre-increment
  reg &operator++() {
    ++_value;
    return *this;
  }

  // Post-increment
  reg operator++(int) {
    reg temp = *this;
    ++_value;
    return temp;
  }

  // Pre-decrement
  reg &operator--() {
    --_value;
    return *this;
  }

  // Post-decrement
  reg operator--(int) {
    reg temp = *this;
    --_value;
    return temp;
  }

  // Const operator[] for read-only bit access
  const bool operator[](uint8_t n) const {
    if (n >= sizeof(T) * 8)
      return false;
    return ((_value & (1 << n)) >> n) != 0;
  }

  // Hex representation
  std::string hex() const {
    std::ostringstream oss;
    oss << std::hex << std::uppercase << std::setw(sizeof(T) * 2)
        << std::setfill('0') << static_cast<uint16_t>(_value);
    return oss.str();
  }
};

using byte = reg<uint8_t>;
using word = reg<uint16_t>;

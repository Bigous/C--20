#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "move_semantics.hpp"

class String {
protected:
  std::vector<char> m_data;

public:
  // cppcheck-suppress noExplicitConstructor
  String(const char *value) : m_data(value, value + strlen(value)) {
    std::cout << "Constructor String const char *(" << static_cast<void*>(this) << ')' << std::endl;
  }

  String(const String &other)
      : m_data(other.m_data.begin(), other.m_data.end()) {
    std::cout << "Construtor String (COPY)(" << static_cast<void*>(this) << ')' << std::endl;
  }

  String(String &&other) : m_data(std::move(other.m_data)) {
    std::cout << "Construtor por String (MOVE)(" << static_cast<void*>(this) << ')' << std::endl;
  }

  auto operator<=>(const String &) const = default;

  ~String() {
    std::cout << "Destrutor String(" << static_cast<void*>(this) << ')' << std::endl;
  }

  void Print() {
    for (const auto &ch : m_data)
      std::cout << ch;
    std::cout << std::endl;
  }
};

class Entity {
protected:
  String m_name;

public:
  // cppcheck-suppress noExplicitConstructor
  Entity(const String &name) : m_name(name) {
    std::cout << "Construtor Entity (COPY)(" << static_cast<void*>(this) << ')' << std::endl;
  }
  // cppcheck-suppress noExplicitConstructor
  Entity(String &&name) : m_name(std::move(name)) {
    std::cout << "Construtor Entity (MOVE)(" << static_cast<void*>(this) << ')' << std::endl;
  }
  ~Entity() { std::cout << "Destrutor Entity(" << static_cast<void*>(this) << ')' << std::endl; }
  void PrintName() { m_name.Print(); }
};

void runMoveSemanticsTests() {
  const char *name = "Richard";
  Entity e(name);
  e.PrintName();

  std::cout << "Fim." << std::endl;
}
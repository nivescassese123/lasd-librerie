
#ifndef TESTABLE_HPP
#define TESTABLE_HPP

/* ************************************************************************** */

#include "container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class TestableContainer : virtual public Container {
  // Must extend Container

private:

  // ...

protected:

  // ...

public:

  // Destructor
  ~TestableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  TestableContainer &operator=(const TestableContainer &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  TestableContainer &operator=(TestableContainer &&) = delete;// Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const TestableContainer &) const = delete;
  bool operator!=(const TestableContainer &) const = delete;

  /* ************************************************************************ */

  // Specific member function

  virtual bool Exists(const Data &) const noexcept = 0; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

}

#endif

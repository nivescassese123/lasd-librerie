
#ifndef CONTAINER_HPP
#define CONTAINER_HPP

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

class Container {

private:

  // ...

protected:

unsigned long size{0}; // Number of elements in the container

  /* ************************************************************************ */

  // Default constructor
   Container() = default;

public:

  // Destructor
  virtual ~Container() = default; // Destructor of abstract types must be declared as virtual

  /* ************************************************************************ */

  // Copy assignment
  Container &operator=(const Container &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  Container &operator=(Container &&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Container &) const noexcept = delete;
  bool operator!=(const Container &) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  inline virtual bool Empty() const noexcept { 
    return 0 == size; }

  inline virtual unsigned long Size() const noexcept { 
    return size; }
};


/* ************************************************************************** */

class ClearableContainer : virtual public Container {
  // Must extend Container

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~ClearableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  ClearableContainer &operator=(const ClearableContainer &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  ClearableContainer &operator=(ClearableContainer &&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ClearableContainer &Clc) const noexcept = delete;
  bool operator!=(const ClearableContainer &Clc) const noexcept = delete;
  /* ************************************************************************ */

  // Specific member functions

  virtual void Clear() = 0; // Clear the container (make it empty)

};

/* ************************************************************************** */

class ResizableContainer : virtual public ClearableContainer {
  // Must extend ClearableContainer

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~ResizableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  ResizableContainer &operator=(const ResizableContainer &Clc) noexcept = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  ResizableContainer &operator=(ResizableContainer &&Clc) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ResizableContainer &Clc) const noexcept = delete;
  bool operator!=(const ResizableContainer &Clc) const noexcept = delete;
  /* ************************************************************************ */

  // Specific member functions

  virtual void Resize(unsigned long) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override {
    Resize(0); // Resize the container to size 0
  }; // Override ClearableContainer member

};

/* ************************************************************************** */

}

#endif

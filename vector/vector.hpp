
#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/container.hpp"


/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Vector : virtual public MutableLinearContainer<Data>,
                virtual public ResizableContainer {
  // Must extend MutableLinearContainer<Data>,
  //             ResizableContainer

private:

  // ...

protected:

   using Container::size;

   Data *elements = nullptr;

public:

  // Default constructor
   Vector() = default; // Default constructor

  /* ************************************************************************ */

  // Specific constructors
  explicit Vector(const unsigned long initialSize) {
    size = initialSize;
    elements = new Data[initialSize]();
  }; // A vector with a given initial dimension
  Vector(const TraversableContainer<Data> &); // A vector obtained from a TraversableContainer
  Vector(MappableContainer<Data> &&); // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
   Vector(const Vector<Data> &);

  // Move constructor
   Vector(Vector<Data> &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~Vector() {
    delete[] elements;
  }; // Destructor of abstract types must be declared as virtual
  

  /* ************************************************************************ */

  // Copy assignment
  
   inline Vector<Data> &operator=(const Vector<Data> &);

  // Move assignment
   inline Vector<Data> &operator=(Vector<Data> &&) noexcept;


  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Vector<Data> &) const noexcept;
  inline bool operator!=(const Vector<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableLinearContainer)

  inline Data &operator[](unsigned long) override;// Override MutableLinearContainer member (must throw std::out_of_range when out of range)

  inline Data &Front() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

  inline Data &Back() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  inline const Data &operator[](unsigned long) const override;// Override LinearContainer member (must throw std::out_of_range when out of range)

  inline const Data &Front() const override;// Override LinearContainer member (must throw std::length_error when empty)

  inline const Data &Back() const override; // Override LinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ResizableContainer)

  void Resize(unsigned long) override; // Override ResizableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  inline void Clear() override; // Override ClearableContainer member

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

template <typename Data>
class SortableVector : virtual public Vector<Data>,
                       virtual public SortableLinearContainer<Data> {
  // Must extend Vector<Data>,
  //             SortableLinearContainer<Data>

private:

  // ...

protected:

  using Container::size;

  // ...

public:

  // Default constructor
  SortableVector() = default; // Default constructor

  /* ************************************************************************ */

  // Specific constructors
  inline SortableVector(unsigned long s) : Vector<Data>::Vector(s){};// A vector with a given initial dimension
  inline SortableVector(const TraversableContainer<Data> &con): Vector<Data>::Vector(con){}; // A vector obtained from a TraversableContainer
  inline SortableVector(MappableContainer<Data> &&con): Vector<Data>::Vector(std::move(con)){}; // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  inline SortableVector(const SortableVector<Data> &con)
  : Vector<Data>::Vector(con){};

  // Move constructor
  inline SortableVector(SortableVector<Data> &&con) noexcept
  : Vector<Data>::Vector(std::move(con)){};


  /* ************************************************************************ */

  // Destructor
  virtual ~SortableVector() = default;

  /* ************************************************************************ */

  // Copy assignment
  inline SortableVector<Data> &operator=(const SortableVector<Data> &con);
  // Move assignment
  inline SortableVector<Data> &operator=(SortableVector<Data> &&con) noexcept;


protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */
}


#include "vector.cpp"

#endif

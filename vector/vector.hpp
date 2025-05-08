
#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

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
    Vector() = default;

  /* ************************************************************************ */

  // Specific constructors
    Vector(const unsigned long); // A vector with a given initial dimension
    Vector(const TraversableContainer<Data> &); // A vector obtained from a TraversableContainer
    Vector(MappableContainer<Data> &&); // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
    Vector(const Vector<Data> &);

  // Move constructor
    Vector(Vector<Data> &&);

  /* ************************************************************************ */

  // Destructor
    virtual ~Vector();

  /* ************************************************************************ */

  // Copy assignment
    inline Vector<Data> &operator=(const Vector<Data> &);

  // Move assignment
    inline Vector<Data> &operator=(Vector<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
    inline bool operator==(const Vector<Data> &) const noexcept;
    inline bool operator!=(const Vector<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableLinearContainer)

    inline Data &operator[](unsigned long) override;  // Override MutableLinearContainer member (must throw std::out_of_range when out of range)

    inline Data &Front() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

    inline Data &Back() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

    inline const Data &operator[](unsigned long) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

    inline const Data &Front() const override; // Override LinearContainer member (must throw std::length_error when empty)

    inline const Data &Back() const override; // Override LinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ResizableContainer)

    inline void Resize(const unsigned long newSize) override; // Override ResizableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

    inline void Clear()override; // Override ClearableContainer member

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

template <typename Data>
class SortableVector : virtual public Vector<Data>,virtual public SortableLinearContainer<Data> {
  // Must extend Vector<Data>,
  //             SortableLinearContainer<Data>

private:

  // ...

protected:

  using Container:: size;

  // ...

public:

  // Default constructor
    SortableVector() = default;

  /* ************************************************************************ */

  // Specific constructors
  inline SortableVector(unsigned long sVec) : Vector<Data>::Vector(sVec){};// A vector with a given initial dimension
  inline SortableVector(const TraversableContainer<Data> &Tcon) : Vector<Data>::Vector(Tcon){};// A vector obtained from a TraversableContainer
  inline SortableVector(MappableContainer<Data> &&Svec) : Vector<Data>::Vector(std::move(Svec)){}; // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
   inline explicit SortableVector(const SortableVector<Data> &Svec): Vector<Data>::Vector(Svec){};

  // Move constructor
  inline explicit SortableVector(SortableVector<Data> &&Svec) noexcept : Vector<Data>::Vector(std::move(Svec)){};

  /* ************************************************************************ */

  // Destructor
   ~SortableVector() = default;

  /* ************************************************************************ */

  // Copy assignment
  inline SortableVector<Data> &operator=(const SortableVector<Data> &);

  // Move assignment
  inline SortableVector<Data> &operator=(SortableVector<Data> &&) noexcept;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif


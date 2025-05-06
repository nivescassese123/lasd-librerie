
#ifndef LINEAR_HPP
#define LINEAR_HPP

/* ************************************************************************** */

#include "mappable.hpp"
#include <algorithm>
#include <climits>
#include <random>
/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class LinearContainer : virtual public PreOrderTraversableContainer<Data>,
                        virtual public PostOrderTraversableContainer<Data> {
  // Must extend PreOrderTraversableContainer<Data>,
  //             PostOrderTraversableContainer<Data>

private:

  // ...

protected:

  using Container::size;

public:

  // Destructor
  virtual ~LinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  LinearContainer &operator=(const LinearContainer &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  LinearContainer &operator=(LinearContainer &&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const LinearContainer &) const noexcept; // Comparison of abstract types is possible.
  inline bool operator!=(const LinearContainer &) const noexcept; // Comparison of abstract types is possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual const Data &operator[](const unsigned long int) const = 0; // (non-mutable version; concrete function must throw std::out_of_range when out of range)

  virtual inline  const Data &Front() const; // (non-mutable version; concrete function must throw std::length_error when empty)

  virtual inline const Data &Back() const; // (non-mutable version; concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  inline void Traverse(TraverseFun fun) const override {
    PreOrderTraverse(fun);
  }; // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  inline void PreOrderTraverse(TraverseFun) const override; // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  inline void PostOrderTraverse(TraverseFun) const override; // Override PostOrderTraversableContainer member

};

/* ************************************************************************** */

template <typename Data>
class MutableLinearContainer : virtual public LinearContainer<Data>,
                               virtual public PreOrderMappableContainer<Data>,
                               virtual public PostOrderMappableContainer<Data> { 
  // Must extend LinearContainer<Data>,
  //             PreOrderMappableContainer<Data>,
  //             PostOrderMappableContainer<Data>

private:

  // ...

protected:

  using Container::size;

public:

  // Destructor
  virtual ~MutableLinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  MutableLinearContainer &operator=(const MutableLinearContainer &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  MutableLinearContainer &operator=(MutableLinearContainer &&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual Data &operator[](const unsigned long int) = 0; // (mutable version; concrete function must throw std::out_of_range when out of range)

  virtual inline Data &Front(); // (mutable version; concrete function must throw std::length_error when empty)

  virtual inline Data &Back(); // (mutable version; concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;

  virtual void Map(MapFun fun) override {
    PreOrderMap(fun);
  };// Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  void PreOrderMap(MapFun) override; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  void PostOrderMap(MapFun) override; // Override PostOrderMappableContainer member

};

template <typename Data>
class SortableLinearContainer : virtual public MutableLinearContainer<Data> {
  // Must extend MutableLinearContainer<Data>

private:

  // ...

protected:

  using Container::size;  

public:

  // Destructor
  virtual ~SortableLinearContainer() = default;

  /* ************************************************************************ */

  SortableLinearContainer &operator=(const SortableLinearContainer &) noexcept = delete;

  SortableLinearContainer &operator=(SortableLinearContainer &&) noexcept = delete;

  /* ************************************************************************ */

  // Specific member function

   inline void Sort() noexcept {
    quickSort(0, size - 1);
  }; // (concrete function must throw std::length_error when empty)
  

protected:

  // Auxiliary member functions

  void quickSort(unsigned long, unsigned long) noexcept;

  void insertionSort(unsigned long, unsigned long) noexcept;

  unsigned long partition(unsigned long, unsigned long) noexcept;

  unsigned long getRandomIndex(unsigned long, unsigned long) const noexcept;

};

}
/* ************************************************************************** */


#include "linear.cpp"

#endif

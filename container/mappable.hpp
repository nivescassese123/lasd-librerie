
#ifndef MAPPABLE_HPP
#define MAPPABLE_HPP

/* ************************************************************************** */

#include <functional>

/* ************************************************************************** */

#include "traversable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class MappableContainer : virtual public TraversableContainer<Data> { 
  // Must extend TraversableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~MappableContainer() noexcept = default;  

  /* ************************************************************************ */

  // Copy assignment
  MappableContainer &operator=(const MappableContainer &) noexcept = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  MappableContainer &operator=(MappableContainer &&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const MappableContainer &) const noexcept = delete;
  bool operator!=(const MappableContainer &) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member function

  using MapFun = std::function<void(Data &)>;

  virtual void Map(const MapFun) = 0;

};

/* ************************************************************************** */

template <typename Data>
class PreOrderMappableContainer : virtual public MappableContainer<Data>,
                                  virtual public PreOrderTraversableContainer<Data> { 
  // Must extend MappableContainer<Data>,
  //             PreOrderTraversableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~PreOrderMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  PreOrderMappableContainer &operator=(const PreOrderMappableContainer &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  PreOrderMappableContainer &operator=(PreOrderMappableContainer &&) noexcept = delete;// Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PreOrderMappableContainer &) const noexcept = delete;
  bool operator!=(const PreOrderMappableContainer &) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member function

  using typename MappableContainer<Data>::MapFun;

  virtual void PreOrderMap(MapFun) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  inline void Map(MapFun) override; // Override MappableContainer member

};

/* ************************************************************************** */

template <typename Data>
class PostOrderMappableContainer: virtual public MappableContainer<Data>,
                                   virtual public PostOrderTraversableContainer<Data> { 
  // Must extend MappableContainer<Data>,
  //             PostOrderTraversableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~PostOrderMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  PostOrderMappableContainer &operator=(const PostOrderMappableContainer &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  PostOrderMappableContainer &operator=(PostOrderMappableContainer &&) noexcept = delete;// Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PostOrderMappableContainer &) const noexcept = delete;
  bool operator!=(const PostOrderMappableContainer &) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member function

  using typename MappableContainer<Data>::MapFun;

  virtual void PostOrderMap(const MapFun) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  inline void Map(const MapFun fun) override; // Override MappableContainer member

};

/* ************************************************************************** */

}

#include "mappable.cpp"

#endif

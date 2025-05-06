
#ifndef SETLST_HPP
#define SETLST_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class SetLst : virtual public Set<Data>, // Must extend Set<Data>,
               virtual public List<Data> { // Must extend List<Data>,
 
private:

  // ...

protected:

  using Container::size;

  // ...

public:

  // Default constructor
   SetLst() = default;;

  /* ************************************************************************ */

  // Specific constructors
  SetLst(const TraversableContainer<Data>& container) {
    container.Traverse([this](const Data& d) { Insert(d); });
  } // A set obtained from a TraversableContainer
  
  SetLst(MappableContainer<Data>&& container) {
    container.Map([this](Data& d) { Insert(std::move(d)); });
  }// A set obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  SetLst(const SetLst& other) : List<Data>(other) {}

  // Move constructor
  SetLst(SetLst&& other) noexcept : List<Data>(std::move(other)) {}


  /* ************************************************************************ */

  // Destructor
   ~SetLst() = default; // Destructor of abstract types must be declared as virtual

  /* ************************************************************************ */

  // Copy assignment
  SetLst& operator=(const SetLst& other) {
    List<Data>::operator=(other);
    return *this;
  }

  // Move assignment
  SetLst& operator=(SetLst&& other) noexcept {
    List<Data>::operator=(std::move(other));
    return *this;
  }
  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const SetLst& other) const {
    if (size != other.size) return false;
    for (const Data& d : *this) {
      if (!other.Exists(d)) return false;
    }
    return true;
  }
  
  bool operator!=(const SetLst& other) const {
    return !(*this == other);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from OrderedDictionaryContainer)

  virtual const Data& Min() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  virtual Data MinNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  virtual void RemoveMin() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

  virtual const Data& Max() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  virtual Data MaxNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  virtual void RemoveMax() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

  virtual const Data& Predecessor(const Data &data) const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  virtual Data PredecessorNRemove(const Data &data) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  virtual void RemovePredecessor(const Data &data) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

  virtual const Data& Successor(const Data &data) const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  virtual Data SuccessorNRemove(const Data& data) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  virtual void RemoveSuccessor(const Data& data) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  virtual bool Insert(const Data &) override; // Override DictionaryContainer member (copy of the value)
  virtual bool Insert(Data &&) override; // Override DictionaryContainer member (move of the value)
  virtual bool Remove(const Data &) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  virtual inline const Data &operator[](const unsigned long) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

  /* ************************************************************************** */

  // Specific member function (inherited from TestableContainer)

  virtual bool Exists(const Data &) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  virtual void Clear() override; // Override ClearableContainer member

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "setlst.cpp"

#endif

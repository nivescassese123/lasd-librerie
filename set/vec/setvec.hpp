
#ifndef SETVEC_HPP
#define SETVEC_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class SetVec : virtual public Set<Data>,
               virtual public ResizableContainer {
  // Must extend Set<Data>,
  //             ResizableContainer

private:

  // ...

protected:

  using Container::size;

  // ...

public:

  // Default constructor
   SetVec() = default; // Default constructor

  /* ************************************************************************ */

  // Specific constructors
  SetVec(const TraversableContainer<Data> &con) {
    for( const Data& element : con) {
      Insert(element);
    }
  }
  
  // SetVec(argument) specifiers; // A set obtained from a MappableContainer
  SetVec(MappableContainer<Data>&& con) {
    for (Data&& val : std::move(con)) {
      Insert(std::move(val));
    }
  }
  /* ************************************************************************ */

  // Copy constructor
  SetVec(const SetVec& other) : elements(other.elements) {
    size = other.size;
  }

  // Move constructor
  SetVec(SetVec&& other) noexcept : elements(std::move(other.elements)) {
    size = std::move(other.size);
  }

  /* ************************************************************************ */

  // Destructor
  ~SetVec() = default;;

  /* ************************************************************************ */

  // Copy assignment
  SetVec& operator=(const SetVec& other) {
    if (this != &other) {
      elements = other.elements;
      size = other.size;
    }
    return *this;
  }
  // Move assignment
  SetVec& operator=(SetVec&& other) noexcept {
    if (this != &other) {
      elements = std::move(other.elements);
      size = std::move(other.size);
    }
    return *this;
  }


  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const SetVec& other) const {
    if (size != other.size) return false;
    for (const Data& val : elements) {
      if (!other.Exists(val)) return false;
    }
    return true;
  }

  bool operator!=(const SetVec& other) const {
    return !(*this == other);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from OrderedDictionaryContainer)

  virtual const Data& Min() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  virtual Data MinNRemove() override;// Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  virtual void RemoveMin() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

  virtual const Data& Max() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  virtual Data MaxNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  virtual void RemoveMax() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

  virtual const Data& Predecessor(const Data&) const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  virtual Data PredecessorNRemove(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  virtual void RemovePredecessor(const Data&) override;// Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

  virtual const Data& Successor(const Data&) const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  virtual Data SuccessorNRemove(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  virtual void RemoveSuccessor(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  virtual bool Insert(const Data&) override; // Override DictionaryContainer member (copy of the value)
  virtual bool Insert(Data&&) override; // Override DictionaryContainer member (move of the value)
  virtual bool Remove(const Data&) override; // Override DictionaryContainer member

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

#include "setvec.cpp"

#endif

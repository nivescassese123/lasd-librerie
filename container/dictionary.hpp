
#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

/* ************************************************************************** */

#include "testable.hpp"
#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class DictionaryContainer: virtual public TestableContainer<Data> {// Must extend TestableContainer<Data>
  

private:

  // ...

protected:

  // ...

public:

  // Destructor
   ~DictionaryContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  DictionaryContainer operator=(const DictionaryContainer&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  DictionaryContainer operator=(DictionaryContainer&&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
    bool operator==(const DictionaryContainer&) = delete; // Comparison of abstract types is not possible.
    bool operator!=(const DictionaryContainer&) = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  //Insert()
    virtual bool Insert(const Data& ) = 0; // Copy of the value
    virtual bool Insert(Data&&) = 0; // Move of the value

  //Remove()  
    virtual bool Remove(const Data&) = 0;

  //InsertAll()
    virtual inline bool InsertAll(const TraversableContainer<Data>&); // Copy of the value; From TraversableContainer; True if all are inserted
    virtual inline bool InsertAll( MappableContainer<Data>&&); // Move of the value; From MappableContainer; True if all are inserted
  
  //RemoveAll()
    virtual inline bool RemoveAll(const TraversableContainer<Data>&); // From TraversableContainer; True if all are removed

  //InsertSome()
    virtual inline bool InsertSome(const TraversableContainer<Data> &);// Copy of the value; From TraversableContainer; True if some is inserted
    virtual inline bool InsertSome(MappableContainer<Data>&&); // Move of the value; From MappableContainer; True if some is inserted
  
  //RemoveSome()
    virtual inline bool RemoveSome(const TraversableContainer<Data>&); // From TraversableContainer; True if some is removed

};

/* ************************************************************************** */

template <typename Data>
class OrderedDictionaryContainer : virtual public DictionaryContainer<Data>{ // Must extend DictionaryContainer<Data>
  

private:

protected:

public:

  // Destructor
    ~OrderedDictionaryContainer() = default;

  /* ************************************************************************ */

   // Copy assignment
  OrderedDictionaryContainer operator=(const OrderedDictionaryContainer&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  OrderedDictionaryContainer operator=(OrderedDictionaryContainer&&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
    bool operator==(const OrderedDictionaryContainer&) = delete; // Comparison of abstract types is not possible.
    bool operator!=(const OrderedDictionaryContainer&) = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  //Min()
    virtual Data Min() const =  0; // (concrete function must throw std::length_error when empty)
    virtual Data MinNRemove() = 0; // (concrete function must throw std::length_error when empty)
    virtual void RemoveMin() = 0; // (concrete function must throw std::length_error when empty)

  //Max()
    virtual Data Max()const =  0; // (concrete function must throw std::length_error when empty)
    virtual Data MaxNRemove() = 0;// (concrete function must throw std::length_error when empty)
    virtual void RemoveMax() = 0; // (concrete function must throw std::length_error when empty)

  //Predecessor()
    virtual Data Predecessor(const Data&)const = 0; // (concrete function must throw std::length_error when not found)
    virtual Data PredecessorNRemove(const Data&) = 0; // (concrete function must throw std::length_error when not found)
    virtual void RemovePredecessor(const Data&) = 0; // (concrete function must throw std::length_error when not found)

  //Successor()
    virtual Data Successor(const Data&)const = 0; // (concrete function must throw std::length_error when not found)
    virtual Data SuccessorNRemove(const Data&) = 0; // (concrete function must throw std::length_error when not found)
    virtual void RemoveSuccessor(const Data&) = 0; // (concrete function must throw std::length_error when not found)

/* ************************************************************************** */  

};
}
#include "dictionary.cpp"

#endif


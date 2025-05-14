
#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

/* ************************************************************************** */

#include "testable.hpp"
#include "mappable.hpp"



namespace lasd {


template <typename Data>
class DictionaryContainer: virtual public TestableContainer<Data> {
  

private:


protected:


public:

  // Destructor
   ~DictionaryContainer() = default;


  // Copy assignment
  DictionaryContainer operator=(const DictionaryContainer&) = delete; 

  // Move assignment
  DictionaryContainer operator=(DictionaryContainer&&) = delete; 

  /* ************************************************************************ */

  // Comparison operators
    bool operator==(const DictionaryContainer&) = delete; 
    bool operator!=(const DictionaryContainer&) = delete; 

  /* ************************************************************************ */

  // Specific member functions

    virtual bool Insert(const Data&) = 0; 
    virtual bool Insert(Data&&) = 0; 
 
    virtual bool Remove(const Data&) = 0;

    virtual inline bool InsertAll(const TraversableContainer<Data>&);
    virtual inline bool InsertAll( MappableContainer<Data>&&); 
  
    virtual inline bool RemoveAll(const TraversableContainer<Data>&);  

    virtual inline bool InsertSome(const TraversableContainer<Data>&);
    virtual inline bool InsertSome(MappableContainer<Data>&&); 
  
    virtual inline bool RemoveSome(const TraversableContainer<Data>&); 

};

/* ************************************************************************** */

template <typename Data>
class OrderedDictionaryContainer : virtual public DictionaryContainer<Data> { 

private:

protected:

public:

  // Destructor
    ~OrderedDictionaryContainer() = default;

  /* ************************************************************************ */

  
  OrderedDictionaryContainer operator=(const OrderedDictionaryContainer&) = delete;

  OrderedDictionaryContainer operator=(OrderedDictionaryContainer&&) = delete; 

  /* ************************************************************************ */

  // Comparison operators
    bool operator==(const OrderedDictionaryContainer&) = delete; 
    bool operator!=(const OrderedDictionaryContainer&) = delete; 

  /* ************************************************************************ */

  // Specific member functions

    virtual Data Min() const =  0; // (concrete function must throw std::length_error when empty)
    virtual Data MinNRemove() = 0; // (concrete function must throw std::length_error when empty)
    virtual void RemoveMin() = 0; // (concrete function must throw std::length_error when empty)

    virtual Data Max()const =  0; // (concrete function must throw std::length_error when empty)
    virtual Data MaxNRemove() = 0;// (concrete function must throw std::length_error when empty)
    virtual void RemoveMax() = 0; // (concrete function must throw std::length_error when empty)

    virtual Data Predecessor(const Data&)const = 0; // (concrete function must throw std::length_error when not found)
    virtual Data PredecessorNRemove(const Data&) = 0; // (concrete function must throw std::length_error when not found)
    virtual void RemovePredecessor(const Data&) = 0; // (concrete function must throw std::length_error when not found)

    virtual Data Successor(const Data&)const = 0; // (concrete function must throw std::length_error when not found)
    virtual Data SuccessorNRemove(const Data&) = 0; // (concrete function must throw std::length_error when not found)
    virtual void RemoveSuccessor(const Data&) = 0; // (concrete function must throw std::length_error when not found)

/* ************************************************************************** */  

};
}
#include "dictionary.cpp"

#endif


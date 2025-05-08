
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

   Vector<Data> elements;

public:

  // Default constructor
     SetVec() = default;

  /* ************************************************************************ */

  // Specific constructors
    SetVec(const TraversableContainer<Data>&); // A set obtained from a TraversableContainer
    SetVec(MappableContainer<Data>&&); // A set obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
    SetVec(const SetVec<Data>&);

  // Move constructor
    SetVec(SetVec<Data>&&);

  /* ************************************************************************ */

  // Destructor
    virtual ~SetVec();

  /* ************************************************************************ */

  // Copy assignment
    inline SetVec<Data> &operator=(const SetVec<Data> &);

  // Move assignment
    inline SetVec<Data> &operator=(SetVec<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
    inline bool operator==(const SetVec<Data> &) const noexcept;
    inline bool operator!=(const SetVec<Data> &) const noexcept;

  /* ************************************************************************ */

   // Specific member functions (inherited from OrderedDictionaryContainer)

    Data Min()const override;// Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
    Data MinNRemove()override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
    void RemoveMin() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

    Data Max()const override;// Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
    Data MaxNRemove()override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
    void RemoveMax() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
 
    Data Predecessor(const Data&)const override;// Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
    Data PredecessorNRemove(const Data&)override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
    void RemovePredecessor(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  
    Data Successor(const Data&)const override;// Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
    Data SuccessorNRemove(const Data&)override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
    void RemoveSuccessor(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

    bool Insert(const Data& ) override; // Override DictionaryContainer member (copy of the value)
    bool Insert(Data&&) override; // Override DictionaryContainer member (move of the value)
    bool Remove(const Data&) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

   const Data& operator[](unsigned long index) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

  /* ************************************************************************** */

  // Specific member function (inherited from TestableContainer)

    bool Exists(const Data &)const noexcept override  ; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

   void Clear() override; // Override ClearableContainer member

protected:

 long FindIndexHelper(const Data&) const;
 long FindIndex(const Data&) const;
 void Resize(unsigned long) override; 

};

/* ************************************************************************** */

}

#include "setvec.cpp"

#endif
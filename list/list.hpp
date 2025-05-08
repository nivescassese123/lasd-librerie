
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List : virtual public MutableLinearContainer<Data>,
             virtual public ClearableContainer {
  // Must extend MutableLinearContainer<Data>,
  //             ClearableContainer

private:

  // ...

protected:



    using Container::size;

  struct Node {

    // Data
      Data element;
      Node* next = nullptr;

    /* ********************************************************************** */

    //Constructor
      inline Node() = default;

    // Specific constructors
      inline Node(const Data &dat) : element(dat){};
      inline Node(Data&&) noexcept;

    /* ********************************************************************** */

    // Copy constructor
      inline Node(const Node &nod) : element(nod.element) {};

    // Move constructor
      inline Node(Node &&) noexcept ;

    /* ********************************************************************** */

    // Destructor
      virtual ~Node();

    /* ********************************************************************** */

    // Comparison operators
      inline bool operator==(const Node &other) const noexcept; 

      inline bool operator!=(const Node &other) const noexcept; 

    /* ********************************************************************** */

    // Specific member functions

      virtual Node * Clone(Node *);

  };

    Node *Tail= nullptr;//posso estendere ma non cancellare
    Node *Head= nullptr;

public:

  // Default constructor
    List() = default;

  /* ************************************************************************ */

  // Specific constructor
    List(const TraversableContainer<Data> &); // A list obtained from a TraversableContainer
    List(MappableContainer<Data> &&); // A list obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
    List(const List &);

  // Move constructor
    List(List &&) noexcept;

  /* ************************************************************************ */

  // Destructor
    virtual ~List();

  /* ************************************************************************ */

  // Copy assignment
    List &operator=(const List &);

  // Move assignment
    List &operator=(List &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
    inline bool operator==(const List &) const noexcept;
    inline bool operator!=(const List &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  //Front
    void InsertAtFront(const Data &); // Copy of the value
    void InsertAtFront(Data &&); // Move of the value
    void RemoveFromFront(); // (must throw std::length_error when empty)
    Data FrontNRemove(); // (must throw std::length_error when empty)

  //Back
    void InsertAtBack(const Data &); // Copy of the value
    void InsertAtBack(Data &&); // Move of the value
    void RemoveFromBack(); // (must throw std::length_error when empty)
    Data BackNRemove() ; // (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableLinearContainer)

    Data &operator[](const unsigned long) override; // Override MutableLinearContainer member (must throw std::out_of_range when out of range)

    Data &Front() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

    Data &Back() override;  // Override MutableLinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

    const Data &operator[](const unsigned long) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

    const Data &Front() const override; // Override LinearContainer member (must throw std::length_error when empty)

    const Data &Back() const override;  // Override LinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

    using typename MappableContainer<Data>::MapFun;

    inline void Map(MapFun fun) override {
    PreOrderMap(fun);
    }

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

    inline void PreOrderMap(MapFun fun) override { PreOrderMap(fun, Head); } // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

    inline void PostOrderMap(MapFun fun) override { PostOrderMap(fun, Head); } // Override PostOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

    using typename TraversableContainer<Data>::TraverseFun;

    inline void Traverse(TraverseFun fun) const override {
    PreOrderTraverse(fun);
    }

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

    inline void PreOrderTraverse(TraverseFun fun) const override{// Override PreOrderTraversableContainer member
    PreOrderTraverse(fun, Head);
    } 

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

    inline void PostOrderTraverse(TraverseFun fun) const override {// Override PostOrderTraversableContainer member
      PostOrderTraverse(fun, Head);
    } 

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

    inline void Clear()noexcept override;  // Override ClearableContainer member

    using TestableContainer<Data>::Exists;

protected:

  // Auxiliary functions, if necessary!

  void PreOrderTraverse(TraverseFun, Node *) const;

  void PostOrderTraverse(TraverseFun, Node *) const;

  void PreOrderMap(MapFun, Node *) const;

  void PostOrderMap(MapFun, Node *) const;

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif

#ifndef TRAVERSABLE_HPP
#define TRAVERSABLE_HPP

/* ************************************************************************** */

#include <functional>

/* ************************************************************************** */

#include "testable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class TraversableContainer : virtual public TestableContainer<Data> {
  

private:

 

protected:

 

public:

  // Destructor
   ~TraversableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
    TraversableContainer& operator=(const TraversableContainer&) = delete; 

  // Move assignment
    TraversableContainer& operator=(TraversableContainer&&) = delete;

  /* ************************************************************************ */

  // Comparison operators
    bool operator==(const TraversableContainer &)const noexcept = delete ; 
    bool operator!=(const TraversableContainer &)const noexcept = delete ;

  /* ************************************************************************ */

  // Specific member function
    using TraverseFun = std::function<void(const Data &)>;
    
    virtual void Traverse(TraverseFun)const = 0;

    template <typename Accumulator>
    using FoldFun = std::function<Accumulator(const Data &, const Accumulator &)>;

    template <typename Accumulator>
    inline Accumulator Fold(FoldFun<Accumulator> fun, Accumulator accumulator) const noexcept;

  /* ************************************************************************ */

  // Specific member function (inherited from TestableContainer)

   inline bool Exists(const Data &) const noexcept override; 

};

/* ************************************************************************** */

template <typename Data>
class PreOrderTraversableContainer : virtual public TraversableContainer<Data> {

private:



protected:

  

public:

  // Destructor
    ~PreOrderTraversableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
    PreOrderTraversableContainer& operator=(const PreOrderTraversableContainer&) = delete;
  // Move assignment
    PreOrderTraversableContainer& operator=(PreOrderTraversableContainer&&) = delete; 

  /* ************************************************************************ */

  // Comparison operators
    bool operator==(const PreOrderTraversableContainer &)const noexcept = delete ; 
    bool operator!=(const PreOrderTraversableContainer &)const noexcept = delete ; 

  /* ************************************************************************ */

  // Specific member function

    using typename TraversableContainer<Data>::TraverseFun;

    virtual void PreOrderTraverse(const TraverseFun) const = 0;

    template <typename Accumulator>
    using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>; 

    template <typename Accumulator>
    inline Accumulator PreOrderFold(FoldFun<Accumulator> , Accumulator ) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

   inline void Traverse(const TraverseFun fun) const override {
     PreOrderTraverse(fun); }  

};

/* ************************************************************************** */

template <typename Data>
class PostOrderTraversableContainer : virtual public TraversableContainer<Data> {  

private:

  

protected:

 

public:

  // Destructor
    ~PostOrderTraversableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
    PostOrderTraversableContainer &operator=(const PostOrderTraversableContainer &) = delete; 

  // Move assignment
    PostOrderTraversableContainer &operator=(PostOrderTraversableContainer &&) noexcept = delete; 

  /* ************************************************************************ */

  // Comparison operators
    bool operator==(const PostOrderTraversableContainer &) const noexcept = delete; 
    bool operator!=(const PostOrderTraversableContainer &) const noexcept = delete; 

  /* ************************************************************************ */

  // Specific member function

    using typename TraversableContainer<Data>::TraverseFun;

    virtual void PostOrderTraverse(TraverseFun) const = 0;

    template <typename Accumulator>
    using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>; 

    template <typename Accumulator>
    inline Accumulator PostOrderFold(FoldFun<Accumulator>, Accumulator) const ;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

    inline void Traverse(const TraverseFun fun) const override {
       PostOrderTraverse(fun); 
      }; 

};

/* ************************************************************************** */

}

#include "traversable.cpp"

#endif
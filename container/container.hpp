#ifndef CONTAINER_HPP
#define CONTAINER_HPP

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

class Container {

private:

  // ...

protected:

  unsigned long size = 0;

  /* ************************************************************************ */

  // Default constructor
    Container() = default;

public:

  // Destructor
    virtual ~Container() = default;

  /* ************************************************************************ */

  // Copy assignment
    Container& operator=(const Container&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
    Container& operator=(Container&&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
    bool operator==(const Container&) = delete; // Comparison of abstract types is not possible.
    bool operator!=(const Container&) = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions 

  //Empty()

    virtual bool Empty()const noexcept{// (concrete function should not throw exceptions)
      return size==0;
    } ; 



  //Size() 

    virtual unsigned long Size()const noexcept{// (concrete function should not throw exceptions)
      return size;
    }

};


/* ************************************************************************** */
/* ************************************************************************** */

class ClearableContainer : virtual public Container{
  

private:

  // ...

protected:

  using Container::size;

public:

  // Destructor
    ~ClearableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  ClearableContainer& operator=(const ClearableContainer&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  ClearableContainer& operator=(ClearableContainer&&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ClearableContainer&) = delete; // Comparison of abstract types is not possible.
  bool operator!=(const ClearableContainer&) = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  //Clear() 

    virtual void Clear() = 0;

};

/* ************************************************************************** */

class ResizableContainer: virtual public ClearableContainer{// Must extend ClearableContainer
  

private:

  // ...

protected:

  using Container::size;

public:

  // Destructor
    ~ResizableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
    ResizableContainer& operator=(const ResizableContainer&) = delete;// Copy assignment of abstract types is not possible.

  // Move assignment
    ResizableContainer& operator=(ResizableContainer&&) = delete;// Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
    bool operator==(const ResizableContainer&) const = delete;// Comparison of abstract types is not possible.
    bool operator!=(const ResizableContainer&) const = delete;// Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  //Resize()

    virtual void Resize(unsigned long newSize) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

    void Clear() override{// Override ClearableContainer member
      Resize(0); 
      }; 

};

/* ************************************************************************** */

}

#endif


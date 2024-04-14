
#ifndef CONTAINER_HPP
#define CONTAINER_HPP

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

#define EMPTY_CONTAINER_MSG "Container is empty."

class Container {

private:

  // ...
  // unsigned long size = 0;

protected:

  // ...
  unsigned long size = 0;

  /* ************************************************************************ */

  // Default constructor
  Container(unsigned long sz = 0) : size(sz) {}
  void setSize (unsigned long sz) {this->size = sz;}

public:

  // Destructor
  virtual ~Container() = default;

  /* ************************************************************************ */

  // Copy assignment
  Container operator=(const Container &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  Container operator=(Container &&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Container &) = delete; // Comparison of abstract types is not possible.
  bool operator!=(const Container &) = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  inline bool Empty() const noexcept {return (this->size == 0);} // (concrete function should not throw exceptions)

  inline unsigned long Size() const noexcept {return this->size;} // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

class ClearableContainer : public virtual Container {
  // Must extend Container

private:

  // ...

protected:

  // ...
  ClearableContainer () = default;

public:

  // Destructor
  virtual ~ClearableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  ClearableContainer operator=(const ClearableContainer &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  ClearableContainer operator=(ClearableContainer &&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ClearableContainer &) = delete; // Comparison of abstract types is not possible.
  bool operator!=(const ClearableContainer &) = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions
  virtual void Clear() = 0;

};

/* ************************************************************************** */

class ResizableContainer : public virtual ClearableContainer {
  // Must extend ClearableContainer

private:

  // ...

protected:

  // ...
  ResizableContainer () = default;

public:

  // Destructor
  virtual ~ResizableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  ResizableContainer operator=(const ResizableContainer &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  ResizableContainer operator=(ResizableContainer &&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ResizableContainer &) = delete; // Comparison of abstract types is not possible.
  bool operator!=(const ResizableContainer &) = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual void Resize(unsigned long) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  inline void Clear() override {this->Resize(0);} // Override ClearableContainer member

};

/* ************************************************************************** */

}

#endif

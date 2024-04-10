
#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/linear.hpp"
#include <stdexcept>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Vector : public ResizableContainer, public LinearContainer<Data> {
  // Must extend ResizableContainer,
  //             LinearContainer<Data>

private:

  // ...
  Data * A = nullptr;

protected:

  // using Container::Size;

  // ...

public:

  // Default constructor
  Vector () = default;

  /* ************************************************************************ */

  // Specific constructors
  Vector (unsigned long); // A vector with a given initial dimension
  // Vector(argument) specifiers; // A vector obtained from a TraversableContainer
  // Vector(argument) specifiers; // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  Vector(const Vector &);

  // Move constructor
  Vector(Vector &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~Vector();

  /* ************************************************************************ */

  // Copy assignment
  Vector operator=(const Vector &);

  // Move assignment
  Vector operator=(Vector &&);

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  // type operator!=(argument) specifiers;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  // type Clear() specifiers; // Override ClearableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ResizableContainer)

  void Resize(unsigned long); // Override ResizableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  inline const Data & operator[](unsigned long idx) const override; // Override (NonMutable) LinearContainer member (must throw std::out_of_range when out of range)
  inline Data & operator[](unsigned long idx) override; // Override (Mutable) LinearContainer member (must throw std::out_of_range when out of range)

  inline const Data & Front() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  inline Data & Front() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  inline const Data & Back() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  inline Data & Back() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

template <typename Data>
class SortableVector {
  // Must extend Vector<Data>,
  //             SortableLinearContainer<Data>

private:

  // ...

protected:

  // using Container::???;

  // ...

public:

  // Default constructor
  // SortableVector() specifiers;

  /* ************************************************************************ */

  // Specific constructors
  // SortableVector(argument) specifiers; // A vector with a given initial dimension
  // SortableVector(argument) specifiers; // A vector obtained from a TraversableContainer
  // SortableVector(argument) specifiers; // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  // SortableVector(argument) specifiers;

  // Move constructor
  // SortableVector(argument) specifiers;

  /* ************************************************************************ */

  // Destructor
  // ~SortableVector() specifiers;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;

  // Move assignment
  // type operator=(argument) specifiers;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
